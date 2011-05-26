#include "ReleaseList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

CReleaseList::CReleaseList(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		std::cout << "Release list node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		int nReleases=Node.nChildNode("release");
		
		std::cout << nReleases << " releases seen" << std::endl;
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
