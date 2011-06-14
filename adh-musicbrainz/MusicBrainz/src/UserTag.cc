#include "musicbrainz4/UserTag.h"

MusicBrainz4::CUserTag::CUserTag(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "UserTag node: " << std::endl << Node.createXMLString(true) << std::endl;

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
				std::cerr << "Unrecognised UserTag node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CUserTag::CUserTag(const CUserTag& Other)
{
	*this=Other;
}

MusicBrainz4::CUserTag& MusicBrainz4::CUserTag::operator =(const CUserTag& Other)
{
	if (this!=&Other)
	{
		m_Name=Other.m_Name;
	}

	return *this;
}

std::string MusicBrainz4::CUserTag::Name() const
{
	return m_Name;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CUserTag& UserTag)
{
	os << "UserTag:" << std::endl;

	os << "\tName:  " << UserTag.Name() << std::endl;

	return os;
}
