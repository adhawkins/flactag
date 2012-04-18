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

#ifndef _FILENAME_BUILDER_H
#define _FILENAME_BUILDER_H

#include <string>

#include "TagName.h"

class CFileNameBuilder
{
public:
	CFileNameBuilder(const tTagMap& m_Tags, const std::string& BasePath, const std::string& SingleDiskFileName, const std::string& MultiDiskFileName);
	CFileNameBuilder(const tTagMap& m_Tags, const std::string& BasePath, const std::string& SingleDiskFileName, const std::string& MultiDiskFileName, const std::string& Extension);

	std::string FileName() const;
private:
	void BuildPath();
	void ReplaceStringFromTag(const std::string& Search, const std::string& ReplaceTag, bool FirstOnly);
	void ReplaceString(const std::string& Search, const std::string& Replace);
	std::string FixString(const std::string& String) const;

	tTagMap m_Tags;
	std::string m_BasePath;
	std::string m_SingleDiskFileName;
	std::string m_MultiDiskFileName;
	std::string m_FileName;
	std::string m_Extension;
};

#endif
