#include "ReleaseList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

MusicBrainzADH::CReleaseList::CReleaseList(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Release list node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		int nReleases=Node.nChildNode("release");
		
		for (int count=0;count<nReleases;count++)
		{
			XMLNode ReleaseNode=Node.getChildNode("release",count);
			m_Releases.push_back(CRelease(ReleaseNode));
		}
	}
}

std::vector<MusicBrainzADH::CRelease> MusicBrainzADH::CReleaseList::Releases() const
{
	return m_Releases;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CReleaseList& ReleaseList)
{
	os << "Release list:" << std::endl;
		
	std::vector<MusicBrainzADH::CRelease> Releases=ReleaseList.Releases();
	std::vector<MusicBrainzADH::CRelease>::const_iterator ThisRelease=Releases.begin();
	while (ThisRelease!=Releases.end())
	{
		os << *ThisRelease;
		
		++ThisRelease;
	}
	
	return os;
}
