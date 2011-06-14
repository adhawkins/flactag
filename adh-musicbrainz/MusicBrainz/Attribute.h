#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

namespace MusicBrainz4
{
	class CAttribute
	{
	public:
		CAttribute(const XMLNode& Node=XMLNode::emptyNode());
		CAttribute(const CAttribute& Other);
		CAttribute& operator =(const CAttribute& Other);

		std::string Text() const;

	private:
		std::string m_Text;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAttribute& Attribute);

#endif
