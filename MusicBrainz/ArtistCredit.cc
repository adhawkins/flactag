#include "ArtistCredit.h"


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

std::vector<MusicBrainz4::CNameCredit> MusicBrainz4::CArtistCredit::NameCredits() const
{
	return m_NameCredits;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CArtistCredit& ArtistCredit)
{
	os << "Artist credit:" << std::endl;

	std::vector<MusicBrainz4::CNameCredit> NameCredits=ArtistCredit.NameCredits();
	std::vector<MusicBrainz4::CNameCredit>::const_iterator ThisNameCredit=NameCredits.begin();
	while (ThisNameCredit!=NameCredits.end())
	{
		os << *ThisNameCredit;

		++ThisNameCredit;
	}

	return os;
}
