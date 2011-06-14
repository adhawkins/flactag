#ifndef _MUSICBRAINZ4_ARTIST_CREDIT_H
#define _MUSICBRAINZ4_ARTIST_CREDIT_H

#include <vector>
#include <iostream>

#include "NameCredit.h"

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CArtistCredit
	{
	public:
		CArtistCredit(const XMLNode& Node=XMLNode::emptyNode());
		CArtistCredit(const CArtistCredit& Other);
		CArtistCredit& operator =(const CArtistCredit& Other);

		std::vector<CNameCredit> NameCredits() const;

	private:
		std::vector<CNameCredit> m_NameCredits;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CArtistCredit& ArtistCredit);

#endif
