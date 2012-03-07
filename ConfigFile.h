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

#ifndef _CONFIG_FILE_H
#define _CONFIG_FILE_H

#include <map>
#include <string>

class CConfigFile
{
public:
	CConfigFile();

	bool LoadFile(const std::string& FileName);
	bool SaveFile(const std::string& FileName) const;
		
	std::string Value(const std::string& Name) const;
	bool BoolValue(const std::string& Name) const;
			
private:
	std::map<std::string,std::string> m_Values;
};

#endif

