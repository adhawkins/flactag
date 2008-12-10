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

     $Id: MusicBrainzInfo.h 163 2008-12-05 16:35:32Z flactag $

----------------------------------------------------------------------------*/

#ifndef _HTTP_FETCH_
#define _HTTP_FETCH_

#include <string>
#include <vector>

class CHTTPFetch
{
public:
	CHTTPFetch();

	int Fetch(const std::string& URL);
	std::vector<unsigned char> Data() const;
	int Result() const;
	int Status() const;
	std::string ErrorMessage() const;
	
private:
	std::vector<unsigned char> m_Data;
	int m_Result;
	int m_Status;
	std::string m_ErrorMessage;

	static int httpResponseReader(void *userdata, const char *buf, size_t len);
};

#endif
