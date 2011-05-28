#include "NameCredit.h"

MusicBrainzADH::CNameCredit::CNameCredit(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Name credit node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("joinphrase"))			
			m_JoinPhrase=Node.getAttribute("joinphrase");
		
		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();
			
			if ("name"==NodeName)
			{
				m_Name=NodeValue;
			}
			else if ("artist"==NodeName)
			{
				m_Artist=CArtist(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised name credit node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

std::string MusicBrainzADH::CNameCredit::JoinPhrase() const
{
	return m_JoinPhrase;
}

std::string MusicBrainzADH::CNameCredit::Name() const
{
	return m_Name;
}

MusicBrainzADH::CArtist MusicBrainzADH::CNameCredit::Artist() const
{
	return m_Artist;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CNameCredit& NameCredit)
{
	os << "Name credit:" << std::endl;
		
	os << "\tJoin phrase: " << NameCredit.JoinPhrase() << std::endl;
	os << "\tName:        " << NameCredit.Name() << std::endl;
	os << NameCredit.Artist() << std::endl;
		
	return os;
}


