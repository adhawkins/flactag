#include "musicbrainz4/NameCredit.h"

#include "musicbrainz4/Artist.h"

MusicBrainz4::CNameCredit::CNameCredit(const XMLNode& Node)
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

MusicBrainz4::CNameCredit::CNameCredit(const CNameCredit& Other)
:	m_Artist(0)
{
	*this=Other;
}

MusicBrainz4::CNameCredit& MusicBrainz4::CNameCredit::operator =(const CNameCredit& Other)
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

MusicBrainz4::CNameCredit::~CNameCredit()
{
	Cleanup();
}

void MusicBrainz4::CNameCredit::Cleanup()
{
	delete m_Artist;
	m_Artist=0;
}

std::string MusicBrainz4::CNameCredit::JoinPhrase() const
{
	return m_JoinPhrase;
}

std::string MusicBrainz4::CNameCredit::Name() const
{
	return m_Name;
}

MusicBrainz4::CArtist *MusicBrainz4::CNameCredit::Artist() const
{
	return m_Artist;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CNameCredit& NameCredit)
{
	os << "Name credit:" << std::endl;

	os << "\tJoin phrase: " << NameCredit.JoinPhrase() << std::endl;
	os << "\tName:        " << NameCredit.Name() << std::endl;

	if (NameCredit.Artist())
		os << *NameCredit.Artist() << std::endl;

	return os;
}


