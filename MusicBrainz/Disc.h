#ifndef _DISC_H
#define _DISC_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

class CDisc
{
public:
	CDisc(const XMLNode& Node=XMLNode::emptyNode());

	std::string ID() const;
	std::string Sectors() const;
		
private:
	std::string m_ID;
	std::string m_Sectors;
		
	friend std::ostream& operator << (std::ostream& os, const CDisc& Disc);
};

#endif
