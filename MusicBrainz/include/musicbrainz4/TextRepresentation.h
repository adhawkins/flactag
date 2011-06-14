#ifndef _MBADH_TEXT_REPRESENTATION_H
#define _MBADH_TEXT_REPRESENTATION_H

#include <iostream>
#include <string>

#include "xmlParser/xmlParser.h"

namespace MusicBrainz4
{
	class CTextRepresentation
	{
	public:
		CTextRepresentation(const XMLNode& Node=XMLNode::emptyNode());
		CTextRepresentation(const CTextRepresentation& Other);
		CTextRepresentation& operator =(const CTextRepresentation& Other);

		std::string Language() const;
		std::string Script() const;

	private:
		std::string m_Language;
		std::string m_Script;

	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTextRepresentation& TextRepresentation);

#endif