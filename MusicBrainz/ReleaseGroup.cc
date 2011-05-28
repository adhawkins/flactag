#include "ReleaseGroup.h"

MusicBrainzADH::CReleaseGroup::CReleaseGroup(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Name credit node: " << std::endl << Node.createXMLString(true) << std::endl;

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
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=CArtistCredit(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised release group node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

std::string MusicBrainzADH::CReleaseGroup::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CReleaseGroup::Title() const
{
	return m_Title;
}

MusicBrainzADH::CArtistCredit MusicBrainzADH::CReleaseGroup::ArtistCredit() const
{
	return m_ArtistCredit;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CReleaseGroup& ReleaseGroup)
{
	os << "Release group:" << std::endl;
		
	os << "\tID:    " << ReleaseGroup.ID() << std::endl;
	os << "\tTitle: " << ReleaseGroup.Title() << std::endl;
	os << ReleaseGroup.ArtistCredit();
	
	return os;
}

