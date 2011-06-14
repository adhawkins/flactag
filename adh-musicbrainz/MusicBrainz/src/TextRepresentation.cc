#include "musicbrainz4/TextRepresentation.h"

MusicBrainz4::CTextRepresentation::CTextRepresentation(const XMLNode& Node)
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

MusicBrainz4::CTextRepresentation::CTextRepresentation(const CTextRepresentation& Other)
{
	*this=Other;
}

MusicBrainz4::CTextRepresentation& MusicBrainz4::CTextRepresentation::operator =(const CTextRepresentation& Other)
{
	if (this!=&Other)
	{
		m_Language=Other.m_Language;
		m_Script=Other.m_Script;
	}

	return *this;
}

std::string MusicBrainz4::CTextRepresentation::Language() const
{
	return m_Language;
}

std::string MusicBrainz4::CTextRepresentation::Script() const
{
	return m_Script;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTextRepresentation& TextRepresentation)
{
	os << "\tText Representation:" << std::endl;

	os << "\t\tLanguage: " << TextRepresentation.Language() << std::endl;
	os << "\t\tScript:   " << TextRepresentation.Script() << std::endl;

	return os;
}
