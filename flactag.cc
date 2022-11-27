/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2012 Andrew Hawkins
   Copyright (C) 2011-2012 Daniel Pocock

   This file is part of flactag.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
	 the Free Software Foundation, either version 3 of the License, or
	 (at your option) any later version.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

#include <slang.h>

#include "config.h"

#include "flactag.h"
#include "Album.h"
#include "AlbumWindow.h"
#include "TrackWindow.h"
#include "FlacInfo.h"
#include "TagsWindow.h"
#include "MusicBrainzInfo.h"
#include "FileNameBuilder.h"
#include "ErrorLog.h"
#include "CommandLine.h"
#include "DiscIDWrapper.h"

#include <vector>
#include <sstream>
#include <iostream>

bool ScreenSizeChanged=false;

static void sigwinch_handler (int sig)
{
	if (sig != SIGWINCH)
		return;
	ScreenSizeChanged=true;
	SLsignal (SIGWINCH, sigwinch_handler);
}

int main(int argc, char *const argv[])
{
	CCommandLine CmdLine(argc,argv);

	if (CmdLine.Valid())
		CFlacTag FlacTag(CmdLine);

	CErrorLog::DumpLog();

	return 0;
}

CFlacTag::CFlacTag(const CCommandLine& CommandLine)
:	m_CommandLine(CommandLine),
	m_SelectedWindow(eWindow_Albums)
{
	if (CommandLine.Version())
	{
		printf("flactag: Version " VERSION "\n");
	}
	else if (CommandLine.DiscID())
	{
		std::vector<std::string> Files=m_CommandLine.FileNames();
		for (std::vector<std::string>::size_type count=0;count<Files.size();count++)
		{
			m_FlacFile=Files[count];

			m_FlacInfo.SetFileName(m_FlacFile);
			m_FlacInfo.Read();

			if (m_FlacInfo.CuesheetFound())
			{
				m_FlacCuesheet=m_FlacInfo.Cuesheet();
				CDiscIDWrapper Calc;
				Calc.FromCuesheet(m_FlacCuesheet);
				std::string DiscID=Calc.ID();
				printf("%s: %s\n",m_FlacFile.c_str(),DiscID.c_str());
			}
		}
	}
	else if (CommandLine.SubmitURL())
	{
		std::vector<std::string> Files=m_CommandLine.FileNames();
		for (std::vector<std::string>::size_type count=0;count<Files.size();count++)
		{
			m_FlacFile=Files[count];

			m_FlacInfo.SetFileName(m_FlacFile);
			m_FlacInfo.Read();

			if (m_FlacInfo.CuesheetFound())
			{
				m_FlacCuesheet=m_FlacInfo.Cuesheet();
				CDiscIDWrapper Calc;
				Calc.FromCuesheet(m_FlacCuesheet);
				std::string SubmitURL=Calc.SubmitURL();
				printf("%s: %s\n",m_FlacFile.c_str(),SubmitURL.c_str());
			}
		}
	}
	else
	{
		std::vector<std::string> Files=m_CommandLine.FileNames();
		for (std::vector<std::string>::size_type count=0;count<Files.size();count++)
		{
			m_FlacFile=Files[count];

			std::string ConfigPath=getenv("HOME");
			ConfigPath+="/.flactag";

			if (!m_ConfigFile.LoadFile(ConfigPath))
				m_ConfigFile.SaveFile(ConfigPath);

			if (LoadData())
			{
				if (CommandLine.Check() || CommandLine.Write() || CommandLine.Rename())
				{
					bool Abort=false;
					int AlbumNum=0;

					if (m_Albums.size()==0)
					{
						printf("%s: No albums found\n",m_FlacFile.c_str());
						Abort=true;
					}

					if (m_Albums.size()>1)
					{
						bool MatchFound=false;

						printf("%s: Multiple albums found\n",m_FlacFile.c_str());

						for (std::vector<CAlbum>::size_type count=0;!MatchFound && count<m_Albums.size();count++)
						{
							if (m_FlacInfo.Tags()[CTagName("MUSICBRAINZ_ALBUMID")]==m_Albums[count].AlbumID())
							{
								AlbumNum=count;
								MatchFound=true;

								std::cout << m_FlacFile.c_str() << ": Album ID in album " << count << " is a match" << std::endl;
							}
						}

						if (!MatchFound)
						{
							printf("%s: No matching album ID found, aborting\n",m_FlacFile.c_str());
							Abort=true;
						}
					}

					if (!Abort)
					{
						CopyTags(AlbumNum);

						if (CommandLine.Check() || CommandLine.Write())
						{
							if (m_WriteInfo.Tags()!=m_FlacInfo.Tags() || m_WriteInfo.CoverArt()!=m_FlacInfo.CoverArt())
							{
								printf("%s: Tags differ\n",m_FlacFile.c_str());

								tTagMap WriteTags=m_WriteInfo.Tags();
								tTagMap FlacTags=m_FlacInfo.Tags();
								tTagMapConstIterator ThisTag=WriteTags.begin();
								while (WriteTags.end()!=ThisTag)
								{
									CTagName Name=(*ThisTag).first;
									CUTF8Tag WriteValue=(*ThisTag).second;

									tTagMapConstIterator FLACTag=FlacTags.find(Name);
									if (FLACTag!=FlacTags.end())
									{
										CUTF8Tag FLACValue=(*FLACTag).second;

										if (WriteValue!=FLACValue)
										{
											if (Name.String()=="COVERART")
												printf("%s: Value for %s has changed\n",m_FlacFile.c_str(),Name.String().c_str());
											else
												printf("%s: Value for %s has changed from %s to %s\n",m_FlacFile.c_str(),Name.String().c_str(),FLACValue.DisplayValue().c_str(),WriteValue.DisplayValue().c_str());
										}
									}
									else
									{
										printf("%s: Tag %s not found in Flac tags\n",m_FlacFile.c_str(),Name.String().c_str());
									}

									++ThisTag;
								}

								ThisTag=FlacTags.begin();
								while (FlacTags.end()!=ThisTag)
								{
									CTagName Name=(*ThisTag).first;

									tTagMapConstIterator OtherTag=WriteTags.find(Name);
									if (OtherTag==WriteTags.end())
										printf("%s: Tag %s not present in tags to be written\n",m_FlacFile.c_str(),Name.String().c_str());

									++ThisTag;
								}

								if (m_WriteInfo.CoverArt() && m_FlacInfo.CoverArt() && m_WriteInfo.CoverArt()!=m_FlacInfo.CoverArt())
									printf("%s: Embedded cover art has changed\n",m_FlacFile.c_str());
								else if (m_WriteInfo.CoverArt() && !m_FlacInfo.CoverArt())
									printf("%s: New embedded cover art\n",m_FlacFile.c_str());
								else if (!m_WriteInfo.CoverArt() && m_FlacInfo.CoverArt())
									printf("%s: Embedded cover art removed\n",m_FlacFile.c_str());
							}
							else
								printf("%s: Tags match\n",m_FlacFile.c_str());

							if (CommandLine.Write())
							{
								bool WriteTags=false;

								if (m_WriteInfo.Tags()!=m_FlacInfo.Tags() || m_WriteInfo.CoverArt()!=m_FlacInfo.CoverArt())
									WriteTags=true;
								else if (CommandLine.ForceWrite())
								{
									printf("%s: Writing tags forced by command line\n",m_FlacFile.c_str());
									WriteTags=true;
								}

								if (WriteTags)
								{
									if (m_FlacInfo.WriteInfo(m_WriteInfo))
									{
										LoadData();
										printf("%s: Tags written\n",m_FlacFile.c_str());
									}
									else
									{
										printf("%s: Error writing tags: '%s'\n",m_FlacFile.c_str(), m_FlacInfo.WriteError().c_str());
										Abort=true;
									}
								}
							}
						}

						if (CommandLine.Rename())
						{
							if (Abort)
							{
								printf("%s: Not renaming due to write error\n",m_FlacFile.c_str());
							}
							else
							{
								if (NeedsRename())
								{
									std::string OrigFile=m_FlacFile;

									if (RenameFile())
										printf("%s: File renamed to %s\n",OrigFile.c_str(),m_RenameFile.c_str());
									else
										printf("%s: Error renaming file to %s\n",OrigFile.c_str(),m_RenameFile.c_str());
								}
							}
						}
					}
				}
				else
					Interactive();
			}
		}
	}
}

void CFlacTag::Interactive()
{
	SLutf8_enable(-1);

	SLtt_get_terminfo();

	if (-1==SLkp_init())
	{
		SLang_verror (0, const_cast<char *>("SLkp_init failed."));
		return;
	}

	if (-1==SLang_init_tty(7,0,0))
	{
		SLang_verror (0, const_cast<char *>("SLang_init_tty."));
		return;
	}

	SLang_set_abort_signal(NULL);
	if (-1==SLsmg_init_smg())
	{
		SLang_verror(0, const_cast<char *>("Error initialising SLmsg\n"));
		return;
	}

	SLsmg_cls();

	CAlbumWindow AlbumWindow(m_Albums);
	CTrackWindow TrackWindow(m_Albums);
	CTagsWindow TagsWindow;

	AlbumWindow.SetSelected(true);
	TrackWindow.SetCurrentAlbum(AlbumWindow.GetCurrentAlbum());

	TagsWindow.SetTags(m_WriteInfo.Tags());

	SLsignal (SIGWINCH, sigwinch_handler);

	SLsmg_init_smg ();

	bool Quit=false;
	bool First=true;

	while (!Quit)
	{
		if (ScreenSizeChanged || First)
		{
			ScreenSizeChanged=false;
			First=false;

			SLtt_get_screen_size ();
			SLsmg_reinit_smg ();

			int WindowHeight=(SLtt_Screen_Rows-5)/2;
			AlbumWindow.SetDimensions(0,0,SLtt_Screen_Cols,5);
			TrackWindow.SetDimensions(0,5,SLtt_Screen_Cols,WindowHeight);
			TagsWindow.SetDimensions(0,5+WindowHeight,SLtt_Screen_Cols,SLtt_Screen_Rows-WindowHeight-6);
		}

		bool Modified=m_FlacInfo.Tags()!=m_WriteInfo.Tags() || m_FlacInfo.CoverArt()!=m_WriteInfo.CoverArt();
		TagsWindow.SetModified(Modified);

		AlbumWindow.Draw();
		TrackWindow.Draw();
		TagsWindow.Draw();

		SLsmg_gotorc(SLtt_Screen_Rows-1,0);
		SLsmg_erase_eol();

		SLsmg_reverse_video();
		SLsmg_write_string(const_cast<char *>("Q"));
		SLsmg_normal_video();
		SLsmg_write_string(const_cast<char *>("uit "));

                SLsmg_reverse_video();
                SLsmg_write_string(const_cast<char *>("M"));
                SLsmg_normal_video();
                SLsmg_write_string(const_cast<char *>("ake cuesheet file "));

		if (m_Albums.size())
		{
			SLsmg_reverse_video();
			SLsmg_write_string(const_cast<char *>("C"));
			SLsmg_normal_video();
			SLsmg_write_string(const_cast<char *>("opy "));
		}

		if (Modified)
		{
			SLsmg_reverse_video();
			SLsmg_write_string(const_cast<char *>("W"));
			SLsmg_normal_video();
			SLsmg_write_string(const_cast<char *>("rite "));
		}

		if (NeedsRename())
		{
			SLsmg_reverse_video();
			SLsmg_write_string(const_cast<char *>("R"));
			SLsmg_normal_video();
			SLsmg_write_string(const_cast<char *>("ename "));
		}

		SLsmg_gotorc(SLtt_Screen_Rows-1,SLtt_Screen_Cols-2);
		SLsmg_write_string(const_cast<char *>(" "));

		SLsmg_refresh();

		if (SLang_input_pending(5))
		{
			int Key=SLkp_getkey();
			switch (Key)
			{
				case SL_KEY_NPAGE:
					switch (m_SelectedWindow)
					{
						case eWindow_Albums:
							AlbumWindow.PageDown();
							TrackWindow.SetCurrentAlbum(AlbumWindow.GetCurrentAlbum());
							break;

						case eWindow_Tracks:
							TrackWindow.PageDown();
							break;

						case eWindow_Tags:
							TagsWindow.PageDown();
							break;
					}
					break;

				case SL_KEY_PPAGE:
					switch (m_SelectedWindow)
					{
						case eWindow_Albums:
							AlbumWindow.PageUp();
							TrackWindow.SetCurrentAlbum(AlbumWindow.GetCurrentAlbum());
							break;

						case eWindow_Tracks:
							TrackWindow.PageUp();
							break;

						case eWindow_Tags:
							TagsWindow.PageUp();
							break;
					}
					break;

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
					if (m_Albums.size())
					{
						CopyTags(AlbumWindow.GetCurrentAlbum());
						TagsWindow.SetTags(m_WriteInfo.Tags());
					}
					else
						SLtt_beep();

					break;

				case 'w':
				case 'W':
					if (Modified)
					{
						if (m_FlacInfo.WriteInfo(m_WriteInfo))
							LoadData();

						TagsWindow.SetTags(m_WriteInfo.Tags());
					}
					else
						SLtt_beep();

					break;

				case 'r':
				case 'R':
					if (NeedsRename())
						RenameFile();
					else
						SLtt_beep();

					break;

				case 'm':
				case 'M':
					MakeCuesheetFile();
					break;

				case 'q':
				case 'Q':
					Quit=true;
					break;

				case SLANG_GETKEY_ERROR:
					//Just ignore errors for now (probably caused by a signal)
					break;

				default:
					SLtt_beep();
					break;
			}
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

	if (m_FlacInfo.CuesheetFound())
	{
		m_FlacCuesheet=m_FlacInfo.Cuesheet();

		m_WriteInfo=CWriteInfo(m_FlacInfo.Tags(),m_FlacInfo.CoverArt());

		CFileNameBuilder FileNameBuilder(m_FlacInfo.Tags(),
																		 m_ConfigFile.Value(CConfigFile::tConfigEntry::BasePath),
																		 m_ConfigFile.Value(CConfigFile::tConfigEntry::SingleDiskFileName),
																		 m_ConfigFile.Value(CConfigFile::tConfigEntry::MultiDiskFileName));

		CFileNameBuilder CueFileNameBuilder(m_FlacInfo.Tags(),
																				m_ConfigFile.Value(CConfigFile::tConfigEntry::BasePath),
																				m_ConfigFile.Value(CConfigFile::tConfigEntry::SingleDiskFileName),
																				m_ConfigFile.Value(CConfigFile::tConfigEntry::MultiDiskFileName),
																				"cue");

		m_RenameFile=FileNameBuilder.FileName();
		m_RenameFileCue=CueFileNameBuilder.FileName();

		tTagMap WriteTags=m_WriteInfo.Tags();

		if (WriteTags.end()==WriteTags.find(CTagName("ALBUM")) &&
				WriteTags.end()==WriteTags.find(CTagName("ARTIST")))
		{
			//Populate write tags with empty tags

			WriteTags[CTagName("ALBUM")]=CUTF8Tag("");
			WriteTags[CTagName("ARTIST")]=CUTF8Tag("");
			WriteTags[CTagName("ARTISTSORT")]=CUTF8Tag("");
			WriteTags[CTagName("YEAR")]=CUTF8Tag("");
			WriteTags[CTagName("DISCNUMBER")]=CUTF8Tag("");

			for (int count=m_FlacCuesheet.FirstTrack();count<=m_FlacCuesheet.LastTrack();count++)
			{
				std::stringstream TagValue;
				TagValue << count;

				WriteTags[CTagName("TRACKNUMBER",count)]=TagValue.str();

				WriteTags[CTagName("TITLE",count)]=CUTF8Tag("");
				WriteTags[CTagName("ARTIST",count)]=CUTF8Tag("");
				WriteTags[CTagName("ARTISTSORT",count)]=CUTF8Tag("");
			}

			m_WriteInfo.SetTags(WriteTags);
			m_WriteInfo.SetCoverArt(CCoverArt());
		}

		int Port=80;
		std::stringstream os;
		os << m_ConfigFile.Value(CConfigFile::tConfigEntry::Port);
		os >> Port;

		CMusicBrainzInfo Info(m_ConfigFile.Value(CConfigFile::tConfigEntry::Server), Port, m_FlacCuesheet, m_CommandLine.OverrideDiscID(), m_CommandLine.OverrideDiscID_val());
		if (Info.LoadInfo(m_FlacFile))
			m_Albums = Info.Albums();
		else
			RetVal = false;
	}
	else
	{
		std::stringstream os;
		os << "No CUESHEET found for '" << m_FlacFile << "'";
		CErrorLog::Log(os.str());
		RetVal=false;
	}

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

	if (RetVal && LastSlashPos<Directory.length()-1)
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
		os << m_ConfigFile.Value(CConfigFile::tConfigEntry::DirectoryCreatePermissions);
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
	{
		std::stringstream os;
		os << "Cannot create " << Directory << ", already exists and is not a directory";
		CErrorLog::Log(os.str());
		RetVal=false;
	}

	return RetVal;
}

bool CFlacTag::MakeDirectory(const std::string& Directory, mode_t Mode) const
{
	bool RetVal=false;

	struct stat Stat;

	if (0!=stat(Directory.c_str(),&Stat))
	{
		if (0==mkdir(Directory.c_str(),Mode))
			RetVal=true;
		else
		{
			std::stringstream os;
			os << "mkdir: " << strerror(errno);
			CErrorLog::Log(os.str());
		}
	}
	else
		RetVal=true;

	return RetVal;
}

bool CFlacTag::MakeCuesheetFile()
{
	bool RetVal=false;
	std::string FlacFilename(m_FlacFile.substr(m_FlacFile.find_last_of('/') + 1));

	m_FlacCuesheet.setFileName(FlacFilename.c_str());

	// If the user hasn't added %E to their ~/.flactag, we shouldn't
	// clobber the FLAC file
	if(m_RenameFileCue == m_RenameFile)
		return false;

	std::ofstream cueFile;
	cueFile.open(m_RenameFileCue.c_str());
	cueFile << m_FlacCuesheet;
	cueFile.close();
	RetVal = true;

	return RetVal;
}

bool CFlacTag::RenameFile()
{
	bool RetVal=false;

	bool Continue=true;

	//First check if the file exists

	struct stat Stat;

	if (0==stat(m_RenameFile.c_str(),&Stat))
		Continue=m_CommandLine.OverwriteExisting();

	if (Continue)
	{
		std::string::size_type LastSlash=m_RenameFile.rfind("/");
		if (std::string::npos!=LastSlash)
		{
			std::string Directory=m_RenameFile.substr(0,LastSlash);
			if (MakeDirectoryTree(Directory))
			{
				if (0==rename(m_FlacFile.c_str(),m_RenameFile.c_str()))
				{
					RetVal=true;

					m_FlacFile=m_RenameFile;
					LoadData();
					if (m_ConfigFile.BoolValue(CConfigFile::tConfigEntry::CreateCuesheetAfterRename))
						MakeCuesheetFile();
				}
				else
				{
					if (EXDEV==errno)
					{
						if (CopyFile(m_FlacFile,m_RenameFile) && 0==unlink(m_FlacFile.c_str()))
						{
							RetVal=true;

							m_FlacFile=m_RenameFile;
							LoadData();
							if (m_ConfigFile.BoolValue(CConfigFile::tConfigEntry::CreateCuesheetAfterRename))
								MakeCuesheetFile();
						}
					}
					else
					{
						std::stringstream os;
						os << "rename: " << strerror(errno);
						CErrorLog::Log(os.str());
					}
				}
			}
		}
	}
	else
	{
		std::stringstream os;
		os << m_RenameFile << " already exists, use --overwrite-existing to force it to be overwritten";
		CErrorLog::Log(os.str());
	}

	return RetVal;
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
							std::stringstream os;
							os << "write: " << strerror(errno);
							CErrorLog::Log(os.str());
							RetVal=false;
						}
					}
					else
					{
						std::stringstream os;
						os << "read: " << strerror(errno);
						CErrorLog::Log(os.str());
						RetVal=false;
					}
				}

				if (RetVal)
				{
					if (0!=fchown(DestFD,Stat.st_uid,Stat.st_gid))
					{
						std::stringstream os;
						os << "chown: " << strerror(errno);
						CErrorLog::Log(os.str());

						//Allow chown to fail (could be on smbfs for example)
					}
				}

				close(DestFD);

				if (!RetVal)
					unlink(Dest.c_str());
			}
			else
			{
				std::stringstream os;
				os << "open dest: " << strerror(errno);
				CErrorLog::Log(os.str());
			}

			close(SrcFD);
		}
		else
		{
			std::stringstream os;
			os << "open source: " << strerror(errno);
			CErrorLog::Log(os.str());
		}
	}

	return RetVal;
}

void CFlacTag::CopyTags(int AlbumNumber)
{
	CAlbum ThisAlbum=m_Albums[AlbumNumber];
	std::vector<CTrack> Tracks=ThisAlbum.Tracks();

	tTagMap WriteTags=m_WriteInfo.Tags();

	for (std::vector<CTrack>::size_type count=0;count<Tracks.size();count++)
	{
		CTrack Track=Tracks[count];

		std::stringstream os;
		os << (int)Track.Number();

		SetTag(WriteTags,CTagName("TRACKNUMBER",Track.Number()),os.str());
		SetTag(WriteTags,CTagName("TITLE",Track.Number()),Track.Name());
		SetTag(WriteTags,CTagName("ARTIST",Track.Number()),Track.Artist());
		SetTag(WriteTags,CTagName("ARTISTSORT",Track.Number()),Track.ArtistSort());
		SetTag(WriteTags,CTagName("MUSICBRAINZ_ARTISTID",Track.Number()),Track.ArtistID());
		SetTag(WriteTags,CTagName("MUSICBRAINZ_TRACKID",Track.Number()),Track.TrackID());
	}

	std::string AlbumName=ThisAlbum.Name().UTF8Value();
	if (ThisAlbum.Type().DisplayValue()=="single")
		AlbumName+=" (Single)";

	SetTag(WriteTags,CTagName("ALBUM"),CUTF8Tag(AlbumName));
	SetTag(WriteTags,CTagName("ARTIST"),ThisAlbum.Artist());
	SetTag(WriteTags,CTagName("ARTISTSORT"),ThisAlbum.ArtistSort());
	SetTag(WriteTags,CTagName("ALBUMARTIST"),CUTF8Tag(""));
	//SetTag(WriteTags,CTagName("ALBUMARTIST"),ThisAlbum.Artist());
	SetTag(WriteTags,CTagName("MUSICBRAINZ_ALBUMARTISTID"),ThisAlbum.ArtistID());
	SetTag(WriteTags,CTagName("MUSICBRAINZ_ALBUMID"),ThisAlbum.AlbumID());
	SetTag(WriteTags,CTagName("MUSICBRAINZ_ALBUMSTATUS"),ThisAlbum.Status());
	SetTag(WriteTags,CTagName("MUSICBRAINZ_ALBUMTYPE"),ThisAlbum.Type());

	WriteTags.erase(CTagName("YEAR"));
	WriteTags.erase(CTagName("DATE"));

	SetTag(WriteTags,CTagName("DATE"),ThisAlbum.Date());

	if (ThisAlbum.DiskNumber()!=-1)
	{
		std::stringstream os;
		os << ThisAlbum.DiskNumber();
		SetTag(WriteTags,CTagName("DISCNUMBER"),os.str());
	}

	SetTag(WriteTags,CTagName("ASIN"),ThisAlbum.ASIN());

	if (ThisAlbum.Artist()==CUTF8Tag("Various Artists"))
		SetTag(WriteTags,CTagName("COMPILATION"),CUTF8Tag("1"));

#ifdef FLAC_API_VERSION_CURRENT
	SetTag(WriteTags,CTagName("COVERART"),CUTF8Tag(""));
	m_WriteInfo.SetCoverArt(ThisAlbum.CoverArt());
#else
	SetTag(WriteTags,CTagName("COVERART"),CUTF8Tag(ThisAlbum.CoverArt()));
#endif

	m_WriteInfo.SetTags(WriteTags);
}

void CFlacTag::SetTag(tTagMap& Tags, const CTagName& TagName, const CUTF8Tag& TagValue)
{
	if (!TagValue.empty())
		Tags[TagName]=TagValue;
	else
		Tags.erase(TagName);
}

bool CFlacTag::NeedsRename() const
{
	bool RetVal=false;

	char *RealPath=realpath(m_FlacFile.c_str(),NULL);
	if (RealPath)
	{
		if (m_RenameFile!=RealPath)
			RetVal=true;

		free(RealPath);
	}

	return RetVal;
}
