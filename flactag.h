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

#ifndef _FLACTAG_H
#define _FLACTAG_H

#include <fstream>
#include <iostream>
#include <string>

#include "Album.h"
#include "TagName.h"
#include "Cuesheet.h"
#include "FlacInfo.h"
#include "ConfigFile.h"
#include "CommandLine.h"
#include "WriteInfo.h"

class CFlacTag
{
public:
	typedef enum
	{
		eWindow_Albums,
		eWindow_Tracks,
		eWindow_Tags
	} tWindowType;

	CFlacTag(const CCommandLine& CommandLine);

private:
	void Interactive();
	bool LoadData();
	bool MakeDirectoryTree(const std::string& Directory) const;
	bool CheckMakeDirectory(const std::string& Directory) const;
	bool MakeDirectory(const std::string& Directory, mode_t Mode) const;
	bool MakeCuesheetFile();
	bool RenameFile();
	bool CopyFile(const std::string& SourceFile, const std::string& DestFile) const;
	void CopyTags(int AlbumNumber);
	void SetTag(tTagMap& Tags, const CTagName& TagName, const CUTF8Tag& TagValue);

	CCommandLine m_CommandLine;
	std::string m_FlacFile;
	std::vector<CAlbum> m_Albums;
	CFlacInfo m_FlacInfo;
	CCuesheet m_FlacCuesheet;
	CWriteInfo m_WriteInfo;
	tWindowType m_SelectedWindow;
	CConfigFile m_ConfigFile;
	std::string m_RenameFile;
	std::string m_RenameFileCue;
};

#endif
