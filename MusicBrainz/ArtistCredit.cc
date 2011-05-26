#include "ArtistCredit.h"

CArtistCredit::CArtistCredit(const XMLNode& Node)
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

std::vector<CNameCredit> CArtistCredit::NameCredits() const
{
	return m_NameCredits;
}

std::ostream& operator << (std::ostream& os, const CArtistCredit& ArtistCredit)
{
	os << "Artist credit:" << std::endl;
		
	std::vector<CNameCredit>::const_iterator ThisNameCredit=ArtistCredit.m_NameCredits.begin();
	while (ThisNameCredit!=ArtistCredit.m_NameCredits.end())
	{
		os << *ThisNameCredit;
		
		++ThisNameCredit;
	}
	
	return os;
}
