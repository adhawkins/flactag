/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006 Andrew Hawkins
   
   This file is part of flactag.
   
   Flactag is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.
   
   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _FLACTAG_H
#define _FLACTAG_H

#include <string>

#include "Album.h"
#include "TagName.h"
#include "Cuesheet.h"
#include "FlacInfo.h"
#include "ConfigFile.h"
#include "CommandLine.h"

class CFlacTag
{
public:
	typedef enum
	{
		eWindow_Albums,
		eWindow_Tracks,
		eWindow_Tags,
	} tWindowType;
	
	CFlacTag(const CCommandLine& CommandLine);
		
private:
	void MainLoop();
	bool LoadData();
	bool MakeDirectoryTree(const std::string& Directory) const;
	bool CheckMakeDirectory(const std::string& Directory) const;
	bool MakeDirectory(const std::string& Directory, mode_t Mode) const;
	void RenameFile();
	bool CopyFile(const std::string& SourceFile, const std::string& DestFile) const;
	void GetAlbumArt(int AlbumNumber) const;
	void CopyTags(int AlbumNumber);
	void SetTag(tTagMap& Tags, const CTagName& TagName, const std::string& TagValue);
	
	CCommandLine m_CommandLine;
	std::string m_FlacFile;
	std::vector<CAlbum> m_Albums;
	CFlacInfo m_FlacInfo;			
	tTagMap m_FlacTags;
	CCuesheet m_FlacCuesheet;
	tTagMap m_WriteTags;
	tWindowType m_SelectedWindow;
	CConfigFile m_ConfigFile;
	std::string m_RenameFile;
};

#endif
