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

#include "musicbrainz4/ArtistCredit.h"

MusicBrainz4::CArtistCredit::CArtistCredit(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Artist credit node: " << std::endl << Node.createXMLString(true) << std::endl;

		int nNameCredits=Node.nChildNode("name-credit");

		for (int count=0;count<nNameCredits;count++)
		{
			XMLNode NameCreditNode=Node.getChildNode("name-credit",count);
			m_NameCredits.push_back(CNameCredit(NameCreditNode));
		}
	}
}

MusicBrainz4::CArtistCredit::CArtistCredit(const CArtistCredit& Other)
{
	*this=Other;
}

MusicBrainz4::CArtistCredit& MusicBrainz4::CArtistCredit::operator =(const CArtistCredit& Other)
{
	if (this!=&Other)
	{
		m_NameCredits=Other.m_NameCredits;
	}

	return *this;
}

std::list<MusicBrainz4::CNameCredit> MusicBrainz4::CArtistCredit::NameCredits() const
{
	return m_NameCredits;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CArtistCredit& ArtistCredit)
{
	os << "Artist credit:" << std::endl;

	std::list<MusicBrainz4::CNameCredit> NameCredits=ArtistCredit.NameCredits();
	std::list<MusicBrainz4::CNameCredit>::const_iterator ThisNameCredit=NameCredits.begin();
	while (ThisNameCredit!=NameCredits.end())
	{
		os << *ThisNameCredit;

		++ThisNameCredit;
	}

	return os;
}
