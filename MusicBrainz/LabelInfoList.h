#ifndef _MBADH_LABEL_INFO_LIST_H
#define _MBADH_LABEL_INFO_LIST_H

#include <vector>
#include <iostream>

#include "LabelInfo.h"

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
{
	class CLabelInfoList
	{
	public:
		CLabelInfoList(const XMLNode& Node=XMLNode::emptyNode());
	
		std::vector<CLabelInfo> LabelInfos() const;
		
	private:
		std::vector<CLabelInfo> m_LabelInfos;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CLabelInfoList& LabelInfoList);

#endif
