#include "Recording.h"

MusicBrainzADH::CRecording::CRecording(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		if (Node.isAttributeSet("id"))			
			m_ID=Node.getAttribute("id");
		
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
			else if ("length"==NodeName)
			{
				m_Length=NodeValue;
			}
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=CArtistCredit(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised recording node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

std::string MusicBrainzADH::CRecording::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CRecording::Title() const
{
	return m_Title;
}

std::string MusicBrainzADH::CRecording::Length() const
{
	return m_Length;
}

MusicBrainzADH::CArtistCredit MusicBrainzADH::CRecording::ArtistCredit() const
{
	return m_ArtistCredit;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRecording& Recording)
{
	os << "Recording:" << std::endl;
		
	os << "\tID:     " << Recording.ID() << std::endl;
	os << "\tTitle:  " << Recording.Title() << std::endl;
	os << "\tLength: " << Recording.Length() << std::endl;
	os << Recording.ArtistCredit() << std::endl;
		
	return os;
}
