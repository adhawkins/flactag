#ifndef _LABEL_INFO_H
#define _LABEL_INFO_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Label.h"

class CLabelInfo
{
public:
	CLabelInfo(const XMLNode& Node=XMLNode::emptyNode());

	std::string CatalogNumber() const;
	CLabel Label() const;

private:
	std::string m_CatalogNumber;
	CLabel m_Label;

	friend std::ostream& operator << (std::ostream& os, const CLabelInfo& LabelInfo);
};

#endif

