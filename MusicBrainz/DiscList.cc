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

bool CDiscList::ContainsDiscID(const std::string& DiscID) const
{
	bool RetVal=false;
	
	std::vector<CDisc>::const_iterator ThisDisc=m_Discs.begin();
	while (!RetVal && ThisDisc!=m_Discs.end())
	{
		CDisc Disc=(*ThisDisc);
		
		std::cout << "Checking disc id '" << Disc.ID() << "' against '" << DiscID << "'" << std::endl;
			
		if (Disc.ID()==DiscID)
			RetVal=true;
			
		++ThisDisc;
	}
	
	return RetVal;
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
