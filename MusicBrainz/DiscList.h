#ifndef _DISC_LIST_H
#define _DISC_LIST_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Disc.h"

class CDiscList
{
public:
	CDiscList(const XMLNode& Node=XMLNode::emptyNode());
	
	std::vector<CDisc> Discs() const;
	
private:
	std::vector<CDisc> m_Discs;

	friend std::ostream& operator << (std::ostream& os, const CDiscList& DiscList);
};

#endif