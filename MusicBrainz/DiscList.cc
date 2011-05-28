#include "ReleaseList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

MusicBrainzADH::CDiscList::CDiscList(const XMLNode& Node)
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

std::vector<MusicBrainzADH::CDisc> MusicBrainzADH::CDiscList::Discs() const
{
	return m_Discs;
}

bool MusicBrainzADH::CDiscList::ContainsDiscID(const std::string& DiscID) const
{
	bool RetVal=false;
	
	std::vector<MusicBrainzADH::CDisc>::const_iterator ThisDisc=m_Discs.begin();
	while (!RetVal && ThisDisc!=m_Discs.end())
	{
		MusicBrainzADH::CDisc Disc=(*ThisDisc);
		
		if (Disc.ID()==DiscID)
			RetVal=true;
			
		++ThisDisc;
	}
	
	return RetVal;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CDiscList& DiscList)
{
	os << "Disc list:" << std::endl;
		
	std::vector<MusicBrainzADH::CDisc> Discs=DiscList.Discs();
	std::vector<MusicBrainzADH::CDisc>::const_iterator ThisDisc=Discs.begin();
	while (ThisDisc!=Discs.end())
	{
		os << *ThisDisc;
		
		++ThisDisc;
	}
	
	return os;
}
