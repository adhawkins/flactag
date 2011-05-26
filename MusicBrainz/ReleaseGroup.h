#ifndef _RELEASE_GROUP_H
#define _RELEASE_GROUP_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "ArtistCredit.h"

class CReleaseGroup
{
public:
	CReleaseGroup(const XMLNode& Node=XMLNode::emptyNode());

	std::string ID() const;
	std::string Title() const;
	CArtistCredit ArtistCredit() const;

private:
	std::string m_ID;
	std::string m_Title;
	CArtistCredit m_ArtistCredit;
		
	friend std::ostream& operator << (std::ostream& os, const CReleaseGroup& ReleaseGroup);
};

#endif
