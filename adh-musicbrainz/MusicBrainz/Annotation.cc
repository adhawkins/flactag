#include "Annotation.h"

MusicBrainz4::CAnnotation::CAnnotation(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Annotation node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("type"))
			m_Type=Node.getAttribute("type");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("entity"==NodeName)
			{
				m_Entity=NodeValue;
			}
			else if ("name"==NodeName)
			{
				m_Name=NodeValue;
			}
			else if ("text"==NodeName)
			{
				m_Text=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised annotatio  node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CAnnotation::CAnnotation(const CAnnotation& Other)
{
	*this=Other;
}

MusicBrainz4::CAnnotation& MusicBrainz4::CAnnotation::operator =(const CAnnotation& Other)
{
	if (this!=&Other)
	{
		m_Type=Other.m_Type;
		m_Entity=Other.m_Entity;
		m_Name=Other.m_Name;
		m_Text=Other.m_Text;
	}

	return *this;
}

std::string MusicBrainz4::CAnnotation::Type() const
{
	return m_Type;
}

std::string MusicBrainz4::CAnnotation::Entity() const
{
	return m_Entity;
}

std::string MusicBrainz4::CAnnotation::Name() const
{
	return m_Name;
}

std::string MusicBrainz4::CAnnotation::Text() const
{
	return m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAnnotation& Annotation)
{
	os << "Annotation:" << std::endl;

	os << "\tType:    " << Annotation.Type() << std::endl;
	os << "\tEntity: " << Annotation.Entity() << std::endl;
	os << "\tName:   " << Annotation.Name() << std::endl;
	os << "\tText:   " << Annotation.Text() << std::endl;

	return os;
}