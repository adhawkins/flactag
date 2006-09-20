#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <slang.h>

#include "flactag.h"
#include "Album.h"
#include "AlbumWindow.h"
#include "TrackWindow.h"
#include "FlacInfo.h"
#include "TagsWindow.h"
#include "MusicBrainzInfo.h"

#include <vector>
#include <sstream>

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
:	m_FlacFile(FlacFile),
	m_SelectedWindow(eWindow_Albums)
{
	std::string ConfigPath=getenv("HOME");
	ConfigPath+="/.flactag";
	
	if (!m_ConfigFile.LoadFile(ConfigPath))
	{
		printf("Creating default config file\n");
		m_ConfigFile.SaveFile(ConfigPath);
	}
	
	if (!LoadData())
		exit(1);
		
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

		if (!m_ConfigFile.Value("BasePath").empty() && 
				!m_ConfigFile.Value("SingleDiskFileName").empty() && 
				!m_ConfigFile.Value("MultiDiskFileName").empty())
		{
			SLsmg_reverse_video();
			SLsmg_write_string("R");
			SLsmg_normal_video();
			SLsmg_write_string("ename ");
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
					os << (int)Track.Number();
					
					m_WriteTags[CTagName("TRACKNUMBER",Track.Number())]=os.str();
					m_WriteTags[CTagName("TITLE",Track.Number())]=Track.Name();
					m_WriteTags[CTagName("ARTIST",Track.Number())]=Track.Artist();
					m_WriteTags[CTagName("ARTISTSORT",Track.Number())]=Track.ArtistSort();
				}

				m_WriteTags[CTagName("ALBUM")]=ThisAlbum.Name();
				m_WriteTags[CTagName("ARTIST")]=ThisAlbum.Artist();
				m_WriteTags[CTagName("ARTISTSORT")]=ThisAlbum.ArtistSort();
				m_WriteTags[CTagName("ALBUMARTIST")]=ThisAlbum.Artist();
								
				if (!ThisAlbum.Date().empty())
				{
					m_WriteTags.erase(CTagName("YEAR"));				
					m_WriteTags.erase(CTagName("DATE"));				
					
					m_WriteTags[CTagName("YEAR")]=ThisAlbum.Date();
				}
				
				if (ThisAlbum.DiskNumber()!=-1)
				{
					std::stringstream os;
					os << ThisAlbum.DiskNumber();
					m_WriteTags[CTagName("DISCNUMBER")]=os.str();
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

bool CFlacTag::LoadData()
{
	bool RetVal=true;
	
	std::string DiskID;
		
	m_FlacInfo.SetFileName(m_FlacFile);
	m_FlacInfo.Read();

	if (!m_FlacInfo.CuesheetFound())
	{
		printf("No CUESHEET found for '%s'\n",m_FlacFile.c_str());
		RetVal=false;
	}
		
	m_FlacTags=m_FlacInfo.Tags();
	m_FlacCuesheet=m_FlacInfo.Cuesheet();

	m_WriteTags=m_FlacTags;
	
	if (m_WriteTags.end()==m_WriteTags.find(CTagName("ALBUM")) &&
			m_WriteTags.end()==m_WriteTags.find(CTagName("ARTIST")))
	{
		//Populate write tags with empty tags
		
		m_WriteTags[CTagName("ALBUM")]="";
		m_WriteTags[CTagName("ARTIST")]="";
		m_WriteTags[CTagName("ARTISTSORT")]="";
		m_WriteTags[CTagName("YEAR")]="";
		m_WriteTags[CTagName("DISCNUMBER")]="";
		
		for (int count=m_FlacCuesheet.FirstTrack();count<=m_FlacCuesheet.LastTrack();count++)
		{
			std::stringstream TagValue;
			TagValue << count;
			
			m_WriteTags[CTagName("TRACKNUMBER",count)]=TagValue.str();
			
			m_WriteTags[CTagName("TITLE",count)]="";
			m_WriteTags[CTagName("ARTIST",count)]="";
			m_WriteTags[CTagName("ARTISTSORT",count)]="";
		}
	}
	
	CMusicBrainzInfo Info(m_FlacCuesheet);
	if (Info.LoadInfo(m_FlacFile))
		m_Albums=Info.Albums();
	else
		RetVal=false;
		
	return RetVal;
}
