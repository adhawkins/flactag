#ifndef _LABEL_INFO_LIST_H
#define _LABEL_INFO_LIST_H

#include <vector>
#include <iostream>

#include "LabelInfo.h"

#include "xmlParser/xmlParser.h"

class CLabelInfoList
{
public:
	CLabelInfoList(const XMLNode& Node=XMLNode::emptyNode());

	std::vector<CLabelInfo> LabelInfos() const;
	
private:
	std::vector<CLabelInfo> m_LabelInfos;

	friend std::ostream& operator << (std::ostream& os, const CLabelInfoList& LabelInfoList);
};

#endif
