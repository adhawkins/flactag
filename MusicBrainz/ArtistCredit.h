#ifndef _ARTIST_CREDIT_H
#define _ARTIST_CREDIT_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "NameCredit.h"

class CArtistCredit
{
public:
	CArtistCredit(const XMLNode& Node=XMLNode::emptyNode());

	std::vector<CNameCredit> NameCredits() const;
			
private:
	std::vector<CNameCredit> m_NameCredits;
		
	friend std::ostream& operator << (std::ostream& os, const CArtistCredit& ArtistCredit);
};

#endif
