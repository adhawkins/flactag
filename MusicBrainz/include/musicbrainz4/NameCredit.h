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

#ifndef _MUSICBRAINZ4_NAME_CREDIT_H
#define _MUSICBRAINZ4_NAME_CREDIT_H

#include <string>
#include <iostream>

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CArtist;

	class CNameCredit
	{
	public:
		CNameCredit(const XMLNode& Node=XMLNode::emptyNode());
		CNameCredit(const CNameCredit& Other);
		CNameCredit& operator =(const CNameCredit& Other);
		~CNameCredit();

		std::string JoinPhrase() const;
		std::string Name() const;
		CArtist *Artist() const;

	private:
		void Cleanup();

		std::string m_JoinPhrase;
		std::string m_Name;
		CArtist *m_Artist;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CNameCredit& NameCredit);

#endif
