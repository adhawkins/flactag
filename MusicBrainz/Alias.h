#ifndef _ALIAS_H
#define _ALIAS_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
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

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CAlias& Alias);

#endif
