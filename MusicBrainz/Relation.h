#ifndef _MBADH_RELATION_H
#define _MBADH_RELATION_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
{
	class CRelation
	{
	public:
		CRelation(const XMLNode& Node=XMLNode::emptyNode());
		
		std::string Type() const;
		std::string Target() const;
			
	private:
		std::string m_Type;
		std::string m_Target;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRelation& Relation);

#endif
