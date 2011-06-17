/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
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

#ifndef _MUSICBRAINZ4_QUERY_H
#define _MUSICBRAINZ4_QUERY_H

#include <string>
#include <map>

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/Release.h"
#include "musicbrainz4/Metadata.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CQuery
	{
	public:
		typedef std::map<std::string,std::string> tParamMap;

		CQuery(const std::string& Server="www.musicbrainz.org");

		CGenericList<CRelease> LookupDiscID(const std::string& DiscID);
		CRelease LookupRelease(const std::string& Release);
		CMetadata Query(const std::string& Resource,const std::string& ID,const tParamMap& Params=tParamMap());

	private:
		std::string m_Server;

		CMetadata PerformQuery(const std::string& Query);
		void WaitRequest() const;
	};
}

#endif
