#ifndef _MEDIUM_LIST_H
#define _MEDIUM_LIST_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Medium.h"

class CMediumList
{
public:
	CMediumList(const XMLNode& Node=XMLNode::emptyNode());
	
	std::vector<CMedium> Media() const;

private:
	std::vector<CMedium> m_Media;

	friend std::ostream& operator << (std::ostream& os, const CMediumList& MediumList);
};

#endif
