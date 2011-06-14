#ifndef _MUSICBRAINZ4_ALIAS_H
#define _MUSICBRAINZ4_ALIAS_H

#include <string>
#include <iostream>

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CAlias
	{
	public:
		CAlias(const XMLNode& Node);
		CAlias(const CAlias& Other);
		CAlias& operator =(const CAlias& Other);

		std::string Type() const;
		std::string Script() const;
		std::string Text() const;

	private:
		std::string m_Type;
		std::string m_Script;
		std::string m_Text;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAlias& Alias);

#endif
