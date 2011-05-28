#include "Medium.h"

#include <sstream>

MusicBrainzADH::CMedium::CMedium(const XMLNode& Node)
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
				std::stringstream os;
				os << NodeValue;
				os << m_Position;
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

int MusicBrainzADH::CMedium::Position() const
{
	return m_Position;
}

std::string MusicBrainzADH::CMedium::Format() const
{
	return m_Format;
}

std::string MusicBrainzADH::CMedium::Title() const
{
	return m_Title;
}

MusicBrainzADH::CDiscList MusicBrainzADH::CMedium::DiscList() const
{
	return m_DiscList;
}

MusicBrainzADH::CTrackList MusicBrainzADH::CMedium::TrackList() const
{
	return m_TrackList;
}

bool MusicBrainzADH::CMedium::ContainsDiscID(const std::string& DiscID) const
{
	return m_DiscList.ContainsDiscID(DiscID);
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CMedium& Medium)
{
	os << "Medium:" << std::endl;
		
	os << "\tPosition: " << Medium.Position() << std::endl;
	os << "\tFormat:   " << Medium.Format() << std::endl;
	os << "\tTitle:    " << Medium.Title() << std::endl;
	os << Medium.DiscList() << std::endl;
	os << Medium.TrackList() << std::endl;
		
	return os;
}
