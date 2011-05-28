#ifndef _MBADH_RELATION_LIST_H
#define _MBADH_RELATION_LIST_H

#include <vector>

#include "xmlParser/xmlParser.h"

#include "Relation.h"

namespace MusicBrainzADH
{
	class CRelationList
	{
	public:
		CRelationList(const XMLNode& Node=XMLNode::emptyNode());
		
		std::vector<CRelation> Relations() const;
		
	private:
		std::vector<CRelation> m_Relations;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRelationList& RelationList);

#endif