#ifndef _USER_TAG_H
#define _USER_TAG_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
{
	class CUserTag
	{
	public:
		CUserTag(const XMLNode& Node);
		CUserTag(const CUserTag& Other);
		CUserTag& operator =(const CUserTag& Other);
		
		std::string Name() const;
			
	private:
		std::string m_Name;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CUserTag& UserTag);

#endif
