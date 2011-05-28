#include "Track.h"

MusicBrainzADH::CTrack::CTrack(const XMLNode& Node)
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
				m_Recording=CRecording(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised track node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

int MusicBrainzADH::CTrack::Position() const
{
	return m_Position;
}

std::string MusicBrainzADH::CTrack::Title() const
{
	return m_Title;
}

MusicBrainzADH::CRecording MusicBrainzADH::CTrack:: Recording() const
{
	return m_Recording;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CTrack& Track)
{
	os << "Track:" << std::endl;
		
	os << "\tPosition: " << Track.Position() << std::endl;
	os << "\tTitle:    " << Track.Title() << std::endl;
	os << Track.Recording() << std::endl;
		
	return os;
}
