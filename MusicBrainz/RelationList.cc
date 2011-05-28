#include "RelationList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

MusicBrainzADH::CRelationList::CRelationList(const XMLNode& Node)
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

std::vector<MusicBrainzADH::CRelation> MusicBrainzADH::CRelationList::Relations() const
{
	return m_Relations;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRelationList& RelationList)
{
	os << "Relation list:" << std::endl;
		
	std::vector<MusicBrainzADH::CRelation> Relations=RelationList.Relations();
	std::vector<MusicBrainzADH::CRelation>::const_iterator ThisRelation=Relations.begin();
	while (ThisRelation!=Relations.end())
	{
		os << *ThisRelation;
		
		++ThisRelation;
	}
	
	return os;
}
