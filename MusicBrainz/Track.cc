#include "Track.h"

CTrack::CTrack(const XMLNode& Node)
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
				m_Position=NodeValue;
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

std::string CTrack::Position() const
{
	return m_Position;
}

std::string CTrack::Title() const
{
	return m_Title;
}

CRecording CTrack:: Recording() const
{
	return m_Recording;
}

std::ostream& operator << (std::ostream& os, const CTrack& Track)
{
	os << "Track:" << std::endl;
		
	os << "\tPosition: " << Track.m_Position << std::endl;
	os << "\tTitle:    " << Track.m_Title << std::endl;
	os << Track.m_Recording << std::endl;
		
	return os;
}
