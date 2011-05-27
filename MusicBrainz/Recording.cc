#include "Recording.h"

CRecording::CRecording(const XMLNode& Node)
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

std::string CRecording::ID() const
{
	return m_ID;
}

std::string CRecording::Title() const
{
	return m_Title;
}

std::string CRecording::Length() const
{
	return m_Length;
}

CArtistCredit CRecording::ArtistCredit() const
{
	return m_ArtistCredit;
}

std::ostream& operator << (std::ostream& os, const CRecording& Recording)
{
	os << "Recording:" << std::endl;
		
	os << "\tID:    " << Recording.m_ID << std::endl;
	os << "\tTitle: " << Recording.m_Title << std::endl;
	os << "\tLength: " << Recording.m_Length<< std::endl;
	os << Recording.m_ArtistCredit << std::endl;
		
	return os;
}
