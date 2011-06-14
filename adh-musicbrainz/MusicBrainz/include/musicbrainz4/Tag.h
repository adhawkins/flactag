#ifndef _TAG_H
#define _TAG_H

#include <string>
#include <iostream>

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CTag
	{
	public:
		CTag(const XMLNode& Node);
		CTag(const CTag& Other);
		CTag& operator =(const CTag& Other);

		int Count() const;
		std::string Name() const;

	private:
		int m_Count;
		std::string m_Name;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTag& Tag);

#endif
