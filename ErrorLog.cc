/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2010 Andrew Hawkins

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

#include "ErrorLog.h"

#include <stdio.h>

const std::vector<std::string>::size_type CErrorLog::m_cMaxSize=100;

std::vector<std::string> Entries;

void CErrorLog::Log(const std::string& String)
{
	Entries.push_back(String);

	while (Entries.size()>m_cMaxSize)
		Entries.erase(Entries.begin());
}

void CErrorLog::DumpLog()
{
	std::vector<std::string>::const_iterator ThisEntry=Entries.begin();
	while (Entries.end()!=ThisEntry)
	{
		fprintf(stderr,"%s\n",(*ThisEntry).c_str());

		++ThisEntry;
	}
}

