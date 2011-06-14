#ifndef _MUSICBRAINZ4_USER_TAG_H
#define _MUSICBRAINZ4_USER_TAG_H

#include <string>
#include <iostream>

#include "xmlParser.h"

namespace MusicBrainz4
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

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CUserTag& UserTag);

#endif
