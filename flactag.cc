#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <slang.h>

#include <musicbrainz/musicbrainz.h>

#include "flactag.h"
#include "Album.h"
#include "AlbumWindow.h"
#include "TrackWindow.h"
#include "FlacInfo.h"
#include "TagsWindow.h"
#include "DiskIDCalculate.h"

#include <vector>
#include <sstream>

void MainLoop(const std::string& DiscID);
std::vector<CAlbum> LoadData(const std::string& FlacFile);

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
		CFlacTag FlacTag(argv[1]);
	}
	else
		printf("Usage: %s flacfile\n",argv[0]);	
		
	return 0;
}

CFlacTag::CFlacTag(const std::string& FlacFile)
:	m_SelectedWindow(eWindow_Albums)
{
	LoadData(FlacFile);
	MainLoop();
}

void CFlacTag::MainLoop()
{
	SLtt_get_terminfo();
	
	if (-1==SLkp_init())
	{
		SLang_doerror ("SLkp_init failed.");
		exit (1);
	}
		
	if (-1==SLang_init_tty(7,0,0))
	{
		SLang_doerror ("SLang_init_tty.");
		exit (1);
	}
	
	SLang_set_abort_signal(NULL);
	if (-1==SLsmg_init_smg())
	{
		SLang_doerror("Error initialising SLmsg\n");
		exit(1);
	}
	
	SLsmg_cls();
	
	int WindowHeight=(SLtt_Screen_Rows-5)/2;
	CAlbumWindow AlbumWindow(0,0,SLtt_Screen_Cols,5,m_Albums);
	CTrackWindow TrackWindow(0,5,SLtt_Screen_Cols,WindowHeight,m_Albums);
	CTagsWindow TagsWindow(0,5+WindowHeight,SLtt_Screen_Cols,SLtt_Screen_Rows-WindowHeight-6);
	
	AlbumWindow.SetSelected(true);
	TrackWindow.SetCurrentAlbum(AlbumWindow.GetCurrentAlbum());
	
	TagsWindow.SetTags(m_WriteTags);
	
	bool Quit=false;
	
	while (!Quit)
	{
		TagsWindow.SetModified(m_FlacTags!=m_WriteTags);
		
		AlbumWindow.Draw();
		TrackWindow.Draw();
		TagsWindow.Draw();
		
		SLsmg_gotorc(SLtt_Screen_Rows-1,0);
		SLsmg_erase_eol();

		SLsmg_reverse_video();
		SLsmg_write_string("Q");
		SLsmg_normal_video();
		SLsmg_write_string("uit ");
		
		if (m_Albums.size())
		{
			SLsmg_reverse_video();
			SLsmg_write_string("C");
			SLsmg_normal_video();
			SLsmg_write_string("opy ");
		}
		
		if (m_FlacTags!=m_WriteTags)
		{
			SLsmg_reverse_video();
			SLsmg_write_string("W");
			SLsmg_normal_video();
			SLsmg_write_string("rite ");
		}
		
		SLsmg_gotorc(SLtt_Screen_Rows-1,SLtt_Screen_Cols-2);
		SLsmg_write_string(" ");

		SLsmg_refresh();
		
		switch (SLkp_getkey())
		{
			case SL_KEY_DOWN:
				switch (m_SelectedWindow)
				{
					case eWindow_Albums:
						AlbumWindow.NextLine();
						TrackWindow.SetCurrentAlbum(AlbumWindow.GetCurrentAlbum());
						break;
						
					case eWindow_Tracks:
						TrackWindow.NextLine();
						break;
						
					case eWindow_Tags:
						TagsWindow.NextLine();
						break;
				}
				break;
				
			case SL_KEY_UP:
				switch (m_SelectedWindow)
				{
					case eWindow_Albums:
						AlbumWindow.PreviousLine();
						TrackWindow.SetCurrentAlbum(AlbumWindow.GetCurrentAlbum());
						break;
						
					case eWindow_Tracks:
						TrackWindow.PreviousLine();
						break;
						
					case eWindow_Tags:
						TagsWindow.PreviousLine();
						break;
				}
				break;
				
			case 9:
				switch (m_SelectedWindow)
				{
					case eWindow_Albums:
						m_SelectedWindow=eWindow_Tracks;
						break;
						
					case eWindow_Tracks:
						m_SelectedWindow=eWindow_Tags;
						break;
						
					case eWindow_Tags:
						m_SelectedWindow=eWindow_Albums;
						break;
				}
				
				AlbumWindow.SetSelected(m_SelectedWindow==eWindow_Albums);
				TrackWindow.SetSelected(m_SelectedWindow==eWindow_Tracks);
				TagsWindow.SetSelected(m_SelectedWindow==eWindow_Tags);
				break;

			case 'c':
			case 'C':
			{
				CAlbum ThisAlbum=m_Albums[AlbumWindow.GetCurrentAlbum()];
				std::vector<CTrack> Tracks=ThisAlbum.Tracks();
				
				for (std::vector<CTrack>::size_type count=0;count<Tracks.size();count++)
				{
					CTrack Track=Tracks[count];
					
					std::stringstream os;
					os << Track.Number();
					
					m_WriteTags[CTagName("TRACKNUMBER",Track.Number())]=os.str();
					m_WriteTags[CTagName("TITLE",Track.Number())]=Track.Name();
					m_WriteTags[CTagName("ARTIST",Track.Number())]=Track.Artist();
				}

				m_WriteTags[CTagName("ALBUM")]=ThisAlbum.Name();
				m_WriteTags[CTagName("ARTIST")]=ThisAlbum.Artist();
				
				if (!ThisAlbum.Date().empty())
				{
					m_WriteTags.erase(CTagName("YEAR"));				
					m_WriteTags.erase(CTagName("DATE"));				
					
					m_WriteTags[CTagName("YEAR")]=ThisAlbum.Date();
				}
				
				if (ThisAlbum.Artist()=="Various Artists")
					m_WriteTags[CTagName("COMPILATION")]="1";
						
				TagsWindow.SetTags(m_WriteTags);			
				break;
			}
			
			case 'w':
			case 'W':
				if (m_FlacInfo.WriteTags(m_WriteTags))
					m_WriteTags=m_FlacInfo.Tags();
					
				break;
								
			case 'q':
			case 'Q':
				Quit=true;
				break;
				
			default:
				SLtt_beep();
				break;
		}
	}

	SLsmg_reset_smg();
	SLang_reset_tty();
}

void CFlacTag::LoadData(const std::string& FlacFile)
{
	std::string DiskID;
		
	m_FlacInfo.SetFileName(FlacFile);
	m_FlacInfo.Read();
	
	m_FlacTags=m_FlacInfo.Tags();
	m_FlacCuesheet=m_FlacInfo.Cuesheet();
	CDiskIDCalculate Calc(m_FlacCuesheet);
	
/*
	tTagMapConstIterator DiskIDTag=m_FlacTags.find(CTagName("DISKID"));
	if (m_FlacTags.end()!=DiskIDTag)
	{
		DiskID=(*DiskIDTag).second;
		printf ("Read DiskID is %s\n",DiskID.c_str());
	}
	else
	{
*/
		DiskID=Calc.DiskID();
		printf ("Calculated DiskID is %s\n",DiskID.c_str());
/*
	}
*/
	
	m_WriteTags=m_FlacTags;
	
	if (m_WriteTags.end()==m_WriteTags.find(CTagName("ALBUM")) &&
			m_WriteTags.end()==m_WriteTags.find(CTagName("ARTIST")))
	{
		//Populate write tags with empty tags
		
		m_WriteTags[CTagName("ALBUM")]="";
		m_WriteTags[CTagName("ARTIST")]="";
		m_WriteTags[CTagName("YEAR")]="";
		
		for (int count=m_FlacCuesheet.FirstTrack();count<=m_FlacCuesheet.LastTrack();count++)
		{
			std::stringstream TagValue;
			m_WriteTags[CTagName("TRACKNUMBER",count)]=TagValue.str();
			
			m_WriteTags[CTagName("TITLE",count)]="";
			m_WriteTags[CTagName("ARTIST",count)]="";
		}
	}
	
  MusicBrainz o;
  bool Ret;

  o.UseUTF8(false);

	//o.SetDebug(1);
	//o.SetDepth(5);
	
  vector<string> Args;
  Args.push_back(DiskID);
  Ret=o.Query(string(MBQ_GetCDInfoFromCDIndexId),&Args);

  if (Ret)
  {
  	int NumAlbums=o.DataInt(MBE_GetNumAlbums);
    if (NumAlbums)
    {
	    for (int count=0; count<NumAlbums; count++)
	    {
		    o.Select(MBS_SelectAlbum, count+1);
	
				std::string AlbumName=o.Data(MBE_AlbumGetAlbumName);
				std::string AlbumArtist=o.Data(MBE_AlbumGetAlbumArtistName);
					
				//printf("Album %s by %s \n",AlbumName.c_str(),AlbumArtist.c_str());

		    int NumTracks=o.DataInt(MBE_AlbumGetNumTracks);

				//printf ("%s - %s (%s)\n",AlbumName.c_str(),AlbumArtist.c_str(),AlbumDate.c_str());
				
				CAlbum Album(AlbumName,AlbumArtist);
	
		    o.Select(MBS_SelectAlbum, count+1);
	
				for (int i=1; i<=NumTracks; i++)
		    {
/*
		    	printf("Track %d is %s by %s\n",
		    							i,
		    							o.Data(MBE_AlbumGetTrackName,i).c_str(),
		    							o.Data(MBE_AlbumGetArtistName,i).c_str());
*/
		    							
		    	CTrack Track(i,o.Data(MBE_AlbumGetTrackName,i),o.Data(MBE_AlbumGetArtistName,i));
					Album.AddTrack(Track);
				}

				o.Select(MBS_SelectReleaseDate,1);				
				
				std::string AlbumDate=o.Data(MBE_ReleaseGetDate).c_str();
				std::string::size_type MinusPos=AlbumDate.find("-");
				if (std::string::npos!=MinusPos)
					AlbumDate=AlbumDate.substr(0,MinusPos);

				Album.SetDate(AlbumDate);
				
				m_Albums.push_back(Album);
			}
		}
		else
		{
			printf("No albums found\n");
			printf("Please submit the DiskID using the following URL:\n%s\n",Calc.SubmitURL().c_str());
			exit(1);
		}
  }
  else
  {
  	std::string Error;
  		
		o.GetQueryError(Error);
		printf("Query failed: %s\n", Error.c_str());
	}
}
