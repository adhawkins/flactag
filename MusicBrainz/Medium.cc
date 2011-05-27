#include "Medium.h"

CMedium::CMedium(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();
			
			if ("position"==NodeName)
			{
				m_Position=NodeValue;
			}
			else if ("format"==NodeName)
			{
				m_Format=NodeValue;
			}
			else if ("disc-list"==NodeName)
			{
				m_DiscList=CDiscList(ChildNode);
			}
			else if ("track-list"==NodeName)
			{
				m_TrackList=CTrackList(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised medium node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

std::string CMedium::Position() const
{
	return m_Position;
}

std::string CMedium::Format() const
{
	return m_Format;
}

CDiscList CMedium::DiscList() const
{
	return m_DiscList;
}

CTrackList CMedium::TrackList() const
{
	return m_TrackList;
}

std::ostream& operator << (std::ostream& os, const CMedium& Medium)
{
	os << "Medium:" << std::endl;
		
	os << "\tPosition: " << Medium.m_Position << std::endl;
	os << "\tFormat:   " << Medium.m_Format << std::endl;
	os << Medium.m_DiscList << std::endl;
	os << Medium.m_TrackList << std::endl;
		
	return os;
}
