#ifndef _MBADH_ARTIST_CREDIT_H
#define _MBADH_ARTIST_CREDIT_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "NameCredit.h"

namespace MusicBrainzADH
{
	class CArtistCredit
	{
	public:
		CArtistCredit(const XMLNode& Node=XMLNode::emptyNode());
	
		std::vector<CNameCredit> NameCredits() const;
				
	private:
		std::vector<CNameCredit> m_NameCredits;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CArtistCredit& ArtistCredit);

#endif
