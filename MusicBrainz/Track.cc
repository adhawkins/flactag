#include "Track.h"

#include <sstream>

#include "Recording.h"

MusicBrainzADH::CTrack::CTrack(const XMLNode& Node)
:	m_Recording(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Track node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
				os >> m_Position;
			}
			else if ("title"==NodeName)
			{
				m_Title=NodeValue;
			}
			else if ("recording"==NodeName)
			{
				m_Recording=new CRecording(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised track node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CTrack::CTrack(const CTrack& Other)
:	m_Recording(0)
{
	*this=Other;
}

MusicBrainzADH::CTrack& MusicBrainzADH::CTrack::operator =(const CTrack& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_Position=Other.m_Position;
		m_Title=Other.m_Title;
		
		if (Other.m_Recording)
			m_Recording=new CRecording(*Other.m_Recording);
	}
	
	return *this;
}

MusicBrainzADH::CTrack::~CTrack()
{
	Cleanup();
}

void MusicBrainzADH::CTrack::Cleanup()
{
	delete m_Recording;
	m_Recording=0;
}

int MusicBrainzADH::CTrack::Position() const
{
	return m_Position;
}

std::string MusicBrainzADH::CTrack::Title() const
{
	return m_Title;
}

MusicBrainzADH::CRecording *MusicBrainzADH::CTrack:: Recording() const
{
	return m_Recording;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CTrack& Track)
{
	os << "Track:" << std::endl;
		
	os << "\tPosition: " << Track.Position() << std::endl;
	os << "\tTitle:    " << Track.Title() << std::endl;

	if (Track.Recording())
		os << *Track.Recording() << std::endl;
		
	return os;
}
