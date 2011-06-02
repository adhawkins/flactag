#include "NoneMBTrack.h"

MusicBrainzADH::CNoneMBTrack::CNoneMBTrack(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "NoneMBTrack node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();
			
			if ("title"==NodeName)
			{
				m_Title=NodeValue;
			}
			else if ("artist"==NodeName)
			{
				m_Artist=NodeValue;
			}
			else if ("length"==NodeName)
			{
				m_Length=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised none MB track node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CNoneMBTrack::CNoneMBTrack(const CNoneMBTrack& Other)
{
	*this=Other;
}

MusicBrainzADH::CNoneMBTrack& MusicBrainzADH::CNoneMBTrack::operator =(const CNoneMBTrack& Other)
{
	if (this!=&Other)
	{
		m_Title=Other.m_Title;
		m_Artist=Other.m_Artist;
		m_Length=Other.m_Length;
	}
	
	return *this;
}

std::string MusicBrainzADH::CNoneMBTrack::Title() const
{
	return m_Title;
}

std::string MusicBrainzADH::CNoneMBTrack::Artist() const
{
	return m_Artist;
}

std::string MusicBrainzADH::CNoneMBTrack::Length() const
{
	return m_Length;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CNoneMBTrack& NoneMBTrack)
{
	os << "NoneMBTrack:" << std::endl;
		
	os << "\tTitle:  " << NoneMBTrack.Title() << std::endl;
	os << "\tArtist: " << NoneMBTrack.Artist() << std::endl;
	os << "\tLength: " << NoneMBTrack.Length() << std::endl;
		
	return os;
}
