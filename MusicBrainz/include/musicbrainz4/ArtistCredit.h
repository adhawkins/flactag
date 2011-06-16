#ifndef _MUSICBRAINZ4_ARTIST_CREDIT_H
#define _MUSICBRAINZ4_ARTIST_CREDIT_H

#include <list>
#include <iostream>

#include "musicbrainz4/NameCredit.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CArtistCredit
	{
	public:
		CArtistCredit(const XMLNode& Node=XMLNode::emptyNode());
		CArtistCredit(const CArtistCredit& Other);
		CArtistCredit& operator =(const CArtistCredit& Other);

		std::list<CNameCredit> NameCredits() const;

	private:
		std::list<CNameCredit> m_NameCredits;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CArtistCredit& ArtistCredit);

#endif
