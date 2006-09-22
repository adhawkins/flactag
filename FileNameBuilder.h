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

#ifndef _FILENAME_BUILDER_H
#define _FILENAME_BUILDER_H

#include <string>

#include "TagName.h"

class CFileNameBuilder
{
public:
	CFileNameBuilder(const tTagMap& m_Tags, const std::string& BasePath, const std::string& SingleDiskFileName, const std::string& MultiDiskFileName);
	
	std::string FileName() const;
private:
	void BuildPath();
	void ReplaceString(const std::string& Search, const std::string& ReplaceTag);
	std::string FixString(const std::string& String) const;

	tTagMap m_Tags;
	std::string m_BasePath;
	std::string m_SingleDiskFileName;
	std::string m_MultiDiskFileName;
	std::string m_FileName;
};

#endif
