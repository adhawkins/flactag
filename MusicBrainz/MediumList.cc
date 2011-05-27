#include "MediumList.h"

CMediumList::CMediumList(const XMLNode& Node)
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

std::vector<CMedium> CMediumList::Media() const
{
	return m_Media;
}

std::ostream& operator << (std::ostream& os, const CMediumList& MediumList)
{
	os << "Medium list:" << std::endl;
		
	std::vector<CMedium>::const_iterator ThisMedium=MediumList.m_Media.begin();
	while (ThisMedium!=MediumList.m_Media.end())
	{
		os << *ThisMedium;
		
		++ThisMedium;
	}
	
	return os;
}
