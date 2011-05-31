#include "NameCredit.h"

#include "Artist.h"

MusicBrainzADH::CNameCredit::CNameCredit(const XMLNode& Node)
:	m_Artist(0)
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
				m_Artist=new CArtist(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised name credit node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CNameCredit::CNameCredit(const CNameCredit& Other)
:	m_Artist(0)
{
	*this=Other;
}

MusicBrainzADH::CNameCredit& MusicBrainzADH::CNameCredit::operator =(const CNameCredit& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_JoinPhrase=Other.m_JoinPhrase;
		m_Name=Other.m_Name;
		
		if (Other.m_Artist)
			m_Artist=new CArtist(*Other.m_Artist);
	}
	
	return *this;
}

MusicBrainzADH::CNameCredit::~CNameCredit()
{
	Cleanup();
}

void MusicBrainzADH::CNameCredit::Cleanup()
{
	delete m_Artist;
	m_Artist=0;
}

std::string MusicBrainzADH::CNameCredit::JoinPhrase() const
{
	return m_JoinPhrase;
}

std::string MusicBrainzADH::CNameCredit::Name() const
{
	return m_Name;
}

MusicBrainzADH::CArtist *MusicBrainzADH::CNameCredit::Artist() const
{
	return m_Artist;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CNameCredit& NameCredit)
{
	os << "Name credit:" << std::endl;
		
	os << "\tJoin phrase: " << NameCredit.JoinPhrase() << std::endl;
	os << "\tName:        " << NameCredit.Name() << std::endl;

	if (NameCredit.Artist())
		os << *NameCredit.Artist() << std::endl;
		
	return os;
}


