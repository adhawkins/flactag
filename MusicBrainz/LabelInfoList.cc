#include "LabelInfoList.h"

MusicBrainzADH::CLabelInfoList::CLabelInfoList(const XMLNode& Node)
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

std::vector<MusicBrainzADH::CLabelInfo> MusicBrainzADH::CLabelInfoList::LabelInfos() const
{
	return m_LabelInfos;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CLabelInfoList& LabelInfoList)
{
	os << "Label info list:" << std::endl;
		
	std::vector<MusicBrainzADH::CLabelInfo> LabelInfos=LabelInfoList.LabelInfos();
	std::vector<MusicBrainzADH::CLabelInfo>::const_iterator ThisLabelInfo=LabelInfos.begin();
	while (ThisLabelInfo!=LabelInfos.end())
	{
		os << *ThisLabelInfo;
		
		++ThisLabelInfo;
	}
	
	return os;
}
