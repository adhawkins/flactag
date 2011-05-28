#include "Relation.h"

MusicBrainzADH::CRelation::CRelation(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Relation node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		if (Node.isAttributeSet("type"))			
			m_Type=Node.getAttribute("type");
		
		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();
			
			if ("target"==NodeName)
			{
				m_Target=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised relation node: '" << NodeName << "'" << std::endl;
			}
		}
	}	
}

std::string MusicBrainzADH::CRelation::Type() const
{
	return m_Type;
}

std::string MusicBrainzADH::CRelation::Target() const
{
	return m_Target;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRelation& Relation)
{
	os << "Relation:" << std::endl;
	os << "\tType:   " << Relation.Type() << std::endl;
	os << "\tTarget: " << Relation.Target() << std::endl;
		
	return os;
}
