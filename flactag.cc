#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <slang.h>

#include "flactag.h"
#include "Album.h"
#include "AlbumWindow.h"
#include "TrackWindow.h"
#include "FlacInfo.h"
#include "TagsWindow.h"
#include "MusicBrainzInfo.h"
#include "FileNameBuilder.h"

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
		m_ConfigFile.SaveFile(ConfigPath);

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

		if (m_RenameFile!=m_FlacFile)
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
					LoadData();
				
				TagsWindow.SetTags(m_WriteTags);
				break;
								
			case 'r':
			case 'R':
				RenameFile();
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
	
	CFileNameBuilder FileNameBuilder(m_FlacTags,
													m_ConfigFile.Value("BasePath"),
													m_ConfigFile.Value("SingleDiskFileName"),
													m_ConfigFile.Value("MultiDiskFileName"));
													
	m_RenameFile=FileNameBuilder.FileName();

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

bool CFlacTag::MakeDirectoryTree(const std::string& Directory) const
{
	bool RetVal=true;
	std::vector<std::string> Components;

	std::string::size_type LastSlashPos=0;
	std::string::size_type SlashPos=Directory.find("/");
	bool First=true;
	while (std::string::npos!=SlashPos)
	{
		if (SlashPos!=0)
		{
			if (First)
				Components.push_back(Directory.substr(LastSlashPos,SlashPos-LastSlashPos));
			else
				Components.push_back(Directory.substr(LastSlashPos+1,SlashPos-LastSlashPos-1));
				
			First=false;
		}
				
		LastSlashPos=SlashPos;
		SlashPos=Directory.find("/",SlashPos+1);
	}
	
	if (RetVal && LastSlashPos!=Directory.length())
		Components.push_back(Directory.substr(LastSlashPos+1));

	std::vector<std::string>::const_iterator ThisComponent=Components.begin();
	std::string MakePath;
	First=true;
		
	while (RetVal && Components.end()!=ThisComponent)
	{
		if (First)
			MakePath=(*ThisComponent);
		else
			MakePath+="/"+(*ThisComponent);
			
		First=false;
		
		RetVal=CheckMakeDirectory(MakePath);
		
		++ThisComponent;
	}	
	
	if (RetVal)
	{
		ThisComponent=Components.begin();
		MakePath="";
		First=true;
			
		int Mode;
		std::stringstream os;
		os << m_ConfigFile.Value("DirectoryCreatePermissions");
		os >> std::oct >> Mode;

		while (RetVal && Components.end()!=ThisComponent)
		{
			if (First)
				MakePath=(*ThisComponent);
			else
				MakePath+="/"+(*ThisComponent);
				
			First=false;
			
			RetVal=MakeDirectory(MakePath,Mode);
			
			++ThisComponent;
		}	
	}
	return RetVal;
}

bool CFlacTag::CheckMakeDirectory(const std::string& Directory) const
{
	bool RetVal=true;
	
	struct stat Stat;
	
	if (0==stat(Directory.c_str(),&Stat) && !S_ISDIR(Stat.st_mode))
		RetVal=false;
	
	return RetVal;
}

bool CFlacTag::MakeDirectory(const std::string& Directory, mode_t Mode) const
{
	bool RetVal=false;
	
	struct stat Stat;

	if (0!=stat(Directory.c_str(),&Stat))
		RetVal=(0==mkdir(Directory.c_str(),Mode));
	else
		RetVal=true;
	
	return RetVal;
}

void CFlacTag::RenameFile()
{
	std::string::size_type LastSlash=m_RenameFile.rfind("/");
	if (std::string::npos!=LastSlash)
	{
		std::string Directory=m_RenameFile.substr(0,LastSlash);
		if (MakeDirectoryTree(Directory))
		{
			if (0==rename(m_FlacFile.c_str(),m_RenameFile.c_str()))
			{
				m_FlacFile=m_RenameFile;
				LoadData();
			}
			else
			{
				if (EXDEV==errno)
				{
					if (CopyFile(m_FlacFile,m_RenameFile) && 0==unlink(m_FlacFile.c_str()))
					{
						m_FlacFile=m_RenameFile;
						LoadData();
					}
				}
			}
		}
	}
}

bool CFlacTag::CopyFile(const std::string& Source, const std::string& Dest) const
{
	bool RetVal=false;
	
	struct stat Stat;
	if (0==stat(Source.c_str(),&Stat))
	{
		int SrcFD,DestFD;
		
		SrcFD=open(Source.c_str(),O_RDONLY);
		if (-1!=SrcFD)
		{
			DestFD=open(Dest.c_str(),O_WRONLY|O_CREAT, Stat.st_mode);
			if (-1!=DestFD)
			{
				RetVal=true;
				
				bool Done=false;
				char Buffer[4096];
				
				while(!Done && RetVal)
				{
					ssize_t Read;
	
					Read=read(SrcFD,Buffer,sizeof(Buffer));
					if (0==Read)
						Done=true;
					else if (Read>0)
					{
						ssize_t Written=write(DestFD,Buffer,Read);
						if (Written!=Read)
						{
							perror("write");
							RetVal=false;
						}
					}
					else
					{
						perror("read");
						RetVal=false;
					}
				}
				
				if (RetVal)
				{
					if (0!=fchown(DestFD,Stat.st_uid,Stat.st_gid))
						RetVal=false;
				}

				close(DestFD);

				if (!RetVal)				
					unlink(Dest.c_str());
			}
			else
				perror("open");
			
			close(SrcFD);
		}
	}
	
	return RetVal;
}
