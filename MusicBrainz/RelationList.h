#ifndef _RELATION_LIST_H
#define _RELATION_LIST_H

#include <vector>

#include "xmlParser/xmlParser.h"

#include "Relation.h"

class CRelationList
{
public:
	CRelationList(const XMLNode& Node=XMLNode::emptyNode());
	
	std::vector<CRelation> Relations() const;
	
private:
	std::vector<CRelation> m_Relations;

	friend std::ostream& operator << (std::ostream& os, const CRelationList& Relations);
};

#endif