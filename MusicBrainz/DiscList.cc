#include "ReleaseList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

CDiscList::CDiscList(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Disc list node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		int nDiscs=Node.nChildNode("disc");
		
		for (int count=0;count<nDiscs;count++)
		{
			XMLNode DiscNode=Node.getChildNode("disc",count);
			m_Discs.push_back(CDisc(DiscNode));
		}
	}
}

std::vector<CDisc> CDiscList::Discs() const
{
	return m_Discs;
}

std::ostream& operator << (std::ostream& os, const CDiscList& DiscList)
{
	os << "Disc list:" << std::endl;
		
	std::vector<CDisc>::const_iterator ThisDisc=DiscList.m_Discs.begin();
	while (ThisDisc!=DiscList.m_Discs.end())
	{
		os << *ThisDisc;
		
		++ThisDisc;
	}
	
	return os;
}
