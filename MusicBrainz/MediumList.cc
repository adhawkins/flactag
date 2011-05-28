#include "MediumList.h"

MusicBrainzADH::CMediumList::CMediumList(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium list node: " << std::endl << Node.createXMLString(true) << std::endl;

		int nMedia=Node.nChildNode("medium");
		
		for (int count=0;count<nMedia;count++)
		{
			XMLNode MediumNode=Node.getChildNode("medium",count);
			m_Media.push_back(CMedium(MediumNode));
		}
	}
}

std::vector<MusicBrainzADH::CMedium> MusicBrainzADH::CMediumList::Media() const
{
	return m_Media;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CMediumList& MediumList)
{
	os << "Medium list:" << std::endl;
		
	std::vector<MusicBrainzADH::CMedium> Media=MediumList.Media();
	std::vector<MusicBrainzADH::CMedium>::const_iterator ThisMedium=Media.begin();
	while (ThisMedium!=Media.end())
	{
		os << *ThisMedium;
		
		++ThisMedium;
	}
	
	return os;
}
