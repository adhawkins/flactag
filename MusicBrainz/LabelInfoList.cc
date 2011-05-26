#include "LabelInfoList.h"

CLabelInfoList::CLabelInfoList(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label info list node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		int nLabelInfos=Node.nChildNode("label-info");
		
		for (int count=0;count<nLabelInfos;count++)
		{
			XMLNode LabelInfoNode=Node.getChildNode("label-info",count);
			m_LabelInfos.push_back(CLabelInfo(LabelInfoNode));
		}
	}
}

std::vector<CLabelInfo> CLabelInfoList::LabelInfos() const
{
	return m_LabelInfos;
}

std::ostream& operator << (std::ostream& os, const CLabelInfoList& LabelInfoList)
{
	os << "Label info list:" << std::endl;
		
	std::vector<CLabelInfo>::const_iterator ThisLabelInfo=LabelInfoList.m_LabelInfos.begin();
	while (ThisLabelInfo!=LabelInfoList.m_LabelInfos.end())
	{
		os << *ThisLabelInfo;
		
		++ThisLabelInfo;
	}
	
	return os;
}
