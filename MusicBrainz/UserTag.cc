#include "UserTag.h"

MusicBrainzADH::CUserTag::CUserTag(const XMLNode& Node)
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

MusicBrainzADH::CUserTag::CUserTag(const CUserTag& Other)
{
	*this=Other;
}

MusicBrainzADH::CUserTag& MusicBrainzADH::CUserTag::operator =(const CUserTag& Other)
{
	if (this!=&Other)
	{
		m_Name=Other.m_Name;
	}
	
	return *this;
}

std::string MusicBrainzADH::CUserTag::Name() const
{
	return m_Name;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CUserTag& UserTag)
{
	os << "UserTag:" << std::endl;
		
	os << "\tName:  " << UserTag.Name() << std::endl;
		
	return os;
}
