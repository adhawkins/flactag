#include "Tag.h"

#include <sstream>

MusicBrainz4::CTag::CTag(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Tag node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("count"))
		{
			std::stringstream os;
			os << Node.getAttribute("type");
			os >> m_Count;
		}

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("name"==NodeName)
			{
				m_Name=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised tag node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CTag::CTag(const CTag& Other)
{
	*this=Other;
}

MusicBrainz4::CTag& MusicBrainz4::CTag::operator =(const CTag& Other)
{
	if (this!=&Other)
	{
		m_Count=Other.m_Count;
		m_Name=Other.m_Name;
	}

	return *this;
}

int MusicBrainz4::CTag::Count() const
{
	return m_Count;
}

std::string MusicBrainz4::CTag::Name() const
{
	return m_Name;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTag& Tag)
{
	os << "Tag:" << std::endl;

	os << "\tCount: " << Tag.Count() << std::endl;
	os << "\tName:  " << Tag.Name() << std::endl;

	return os;
}
