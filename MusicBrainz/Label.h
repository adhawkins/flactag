#ifndef _LABEL_H
#define _LABEL_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

class CLabel
{
public:
	CLabel(const XMLNode& Node=XMLNode::emptyNode());

	std::string ID() const;
	std::string Name() const;
	std::string SortName() const;
	std::string LabelCode() const;

private:
	std::string m_ID;
	std::string m_Name;
	std::string m_SortName;
	std::string m_LabelCode;

	friend std::ostream& operator << (std::ostream& os, const CLabel& Label);
};

#endif
