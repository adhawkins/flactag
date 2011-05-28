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
			else if ("title"==NodeName)
			{
				m_Title=NodeValue;
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

std::string CMedium::Title() const
{
	return m_Title;
}

CDiscList CMedium::DiscList() const
{
	return m_DiscList;
}

CTrackList CMedium::TrackList() const
{
	return m_TrackList;
}

bool CMedium::ContainsDiscID(const std::string& DiscID) const
{
	return m_DiscList.ContainsDiscID(DiscID);
}

std::ostream& operator << (std::ostream& os, const CMedium& Medium)
{
	os << "Medium:" << std::endl;
		
	os << "\tPosition: " << Medium.m_Position << std::endl;
	os << "\tFormat:   " << Medium.m_Format << std::endl;
	os << "\tTitle:    " << Medium.m_Title << std::endl;
	os << Medium.m_DiscList << std::endl;
	os << Medium.m_TrackList << std::endl;
		
	return os;
}
