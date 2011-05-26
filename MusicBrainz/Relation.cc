#include "Relation.h"

CRelation::CRelation(const XMLNode& Node)
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

std::string CRelation::Type() const
{
	return m_Type;
}

std::string CRelation::Target() const
{
	return m_Target;
}

std::ostream& operator << (std::ostream& os, const CRelation& Relation)
{
	os << "Relation:" << std::endl;
	os << "\tType:   " << Relation.m_Type << std::endl;
	os << "\tTarget: " << Relation.m_Target << std::endl;
		
	return os;
}
