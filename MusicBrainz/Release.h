#ifndef _RELEASE_H
#define _RELEASE_H

#include <string>

#include "xmlParser/xmlParser.h"

class CRelease
{
public:
	CRelease(const XMLNode& Node=XMLNode::emptyNode());
	
	std::string ID() const;
		
private:
	std::string m_ID;
};

#endif