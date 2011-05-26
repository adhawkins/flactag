#ifndef _ARTIST_H
#define _ARTIST_h

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

class CArtist
{
public:
	CArtist(const XMLNode& Node=XMLNode::emptyNode());

	std::string ID() const;
	std::string Name() const;
	std::string SortName() const;
	std::string Disambiguation() const;

private:
	std::string m_ID;
	std::string m_Name;
	std::string m_SortName;
	std::string m_Disambiguation;

	friend std::ostream& operator << (std::ostream& os, const CArtist& Artist);
};

#endif
