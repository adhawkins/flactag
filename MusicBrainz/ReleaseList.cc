#include "ReleaseList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

CReleaseList::CReleaseList(const XMLNode& Node)
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

std::vector<CRelease> CReleaseList::Releases() const
{
	return m_Releases;
}

std::ostream& operator << (std::ostream& os, const CReleaseList& ReleaseList)
{
	os << "Release list:" << std::endl;
		
	std::vector<CRelease>::const_iterator ThisRelease=ReleaseList.m_Releases.begin();
	while (ThisRelease!=ReleaseList.m_Releases.end())
	{
		os << *ThisRelease;
		
		++ThisRelease;
	}
	
	return os;
}
