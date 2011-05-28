#include "ArtistCredit.h"

MusicBrainzADH::CArtistCredit::CArtistCredit(const XMLNode& Node)
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

std::vector<MusicBrainzADH::CNameCredit> MusicBrainzADH::CArtistCredit::NameCredits() const
{
	return m_NameCredits;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CArtistCredit& ArtistCredit)
{
	os << "Artist credit:" << std::endl;
	
	std::vector<MusicBrainzADH::CNameCredit> NameCredits=ArtistCredit.NameCredits();	
	std::vector<MusicBrainzADH::CNameCredit>::const_iterator ThisNameCredit=NameCredits.begin();
	while (ThisNameCredit!=NameCredits.end())
	{
		os << *ThisNameCredit;
		
		++ThisNameCredit;
	}
	
	return os;
}
