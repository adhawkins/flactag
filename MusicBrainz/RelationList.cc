#include "RelationList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

CRelationList::CRelationList(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Relation list node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		int nRelations=Node.nChildNode("relation");
		
		for (int count=0;count<nRelations;count++)
		{
			XMLNode RelationNode=Node.getChildNode("relation",count);
			m_Relations.push_back(CRelation(RelationNode));
		}
	}
}

std::vector<CRelation> CRelationList::Relations() const
{
	return m_Relations;
}

std::ostream& operator << (std::ostream& os, const CRelationList& RelationList)
{
	os << "Relation list:" << std::endl;
		
	std::vector<CRelation>::const_iterator ThisRelation=RelationList.m_Relations.begin();
	while (ThisRelation!=RelationList.m_Relations.end())
	{
		os << *ThisRelation;
		
		++ThisRelation;
	}
	
	return os;
}
