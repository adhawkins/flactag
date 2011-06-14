#ifndef _MUSICBRAINZ4_LIFESPAN_H
#define _MUSICBRAINZ4_LIFESPAN_H

#include <string>
#include <iostream>

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CLifespan
	{
	public:
		CLifespan(const XMLNode& Node=XMLNode::emptyNode());
		CLifespan(const CLifespan& Other);
		CLifespan& operator =(const CLifespan& Other);

		std::string Begin() const;
		std::string End() const;

	private:
		std::string m_Begin;
		std::string m_End;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLifespan& Lifespan);

#endif
