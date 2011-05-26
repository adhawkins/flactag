#ifndef _RELEASE_LIST_H
#define _RELEASE_LIST_H

#include <vector>

#include "xmlParser/xmlParser.h"

#include "Release.h"

class CReleaseList
{
public:
	CReleaseList(const XMLNode& Node=XMLNode::emptyNode());
	
	std::vector<CRelease> Releases() const;
	
private:
	std::vector<CRelease> m_Releases;
};

#endif