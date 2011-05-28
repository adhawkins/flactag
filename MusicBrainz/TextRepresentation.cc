#include "TextRepresentation.h"

MusicBrainzADH::CTextRepresentation::CTextRepresentation(const XMLNode& Node)
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

std::string MusicBrainzADH::CTextRepresentation::Language() const
{
	return m_Language;
}

std::string MusicBrainzADH::CTextRepresentation::Script() const
{
	return m_Script;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CTextRepresentation& TextRepresentation)
{
	os << "\tText Representation:" << std::endl;
		
	os << "\t\tLanguage: " << TextRepresentation.Language() << std::endl;
	os << "\t\tScript:   " << TextRepresentation.Script() << std::endl;
	
	return os;
}

