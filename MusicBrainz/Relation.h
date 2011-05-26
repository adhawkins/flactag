#ifndef _RELATION_H
#define _RELATION_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

class CRelation
{
public:
	CRelation(const XMLNode& Node=XMLNode::emptyNode());
	
	std::string Type() const;
	std::string Target() const;
		
private:
	std::string m_Type;
	std::string m_Target;
		
	friend std::ostream& operator << (std::ostream& os, const CRelation& Relation);
};

#endif
