#ifndef _MEDIUM_H
#define _MEDIUM_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "DiscList.h"
#include "TrackList.h"

class CMedium
{
public:
	CMedium(const XMLNode& Node=XMLNode::emptyNode());

	std::string Position() const;
	std::string Format() const;
	std::string Title() const;
	CDiscList DiscList() const;
	CTrackList TrackList() const;

	bool ContainsDiscID(const std::string& DiscID) const;
			
private:
	std::string m_Position;
	std::string m_Format;
	std::string m_Title;
	CDiscList m_DiscList;
	CTrackList m_TrackList;

	friend std::ostream& operator << (std::ostream& os, const CMedium& Medium);
};

#endif
