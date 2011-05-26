#include "TextRepresentation.h"

CTextRepresentation::CTextRepresentation(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Text representation node: " << std::endl << Node.createXMLString(true) << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();
			
			if ("language"==NodeName)
			{
				m_Language=NodeValue;
			}
			else if ("script"==NodeName)
			{
				m_Script=NodeValue;
			}
		}
	}
}

std::string CTextRepresentation::Language() const
{
	return m_Language;
}

std::string CTextRepresentation::Script() const
{
	return m_Script;
}

std::ostream& operator << (std::ostream& os, const CTextRepresentation& TextRepresentation)
{
	os << "\tText Representation:" << std::endl;
		
	os << "\t\tLanguage: " << TextRepresentation.m_Language << std::endl;
	os << "\t\tScript:   " << TextRepresentation.m_Script << std::endl;
	return os;
}

