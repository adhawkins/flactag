#ifndef _TEXT_REPRESENTATION_H
#define _TEXT_REPRESENTATION_H

#include <iostream>
#include <string>

#include "xmlParser/xmlParser.h"

class CTextRepresentation
{
public:
	CTextRepresentation(const XMLNode& Node=XMLNode::emptyNode());
	
	std::string Language() const;
	std::string Script() const;
		
private:
	std::string m_Language;
	std::string m_Script;
		
	friend std::ostream& operator << (std::ostream& os, const CTextRepresentation& TextRepresentation);

};

#endif