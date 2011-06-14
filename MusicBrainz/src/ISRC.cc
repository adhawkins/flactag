#include "musicbrainz4/ISRC.h"

MusicBrainz4::CISRC::CISRC(const XMLNode& Node)
:	m_RecordingList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISRC node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_ID=Node.getAttribute("id");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("recording-list"==NodeName)
			{
				m_RecordingList=new CGenericList<CRecording>(ChildNode,"recording");
			}
			else
			{
				std::cerr << "Unrecognised ISRC node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CISRC::CISRC(const CISRC& Other)
:	m_RecordingList(0)
{
	*this=Other;
}

MusicBrainz4::CISRC& MusicBrainz4::CISRC::operator =(const CISRC& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_ID=Other.m_ID;

		if (Other.m_RecordingList)
			m_RecordingList=new CGenericList<CRecording>(*Other.m_RecordingList);
	}

	return *this;
}

MusicBrainz4::CISRC::~CISRC()
{
	Cleanup();
}

void MusicBrainz4::CISRC::Cleanup()
{
	delete m_RecordingList;
	m_RecordingList=0;
}

std::string MusicBrainz4::CISRC::ID() const
{
	return m_ID;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRecording> *MusicBrainz4::CISRC::RecordingList() const
{
	return m_RecordingList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CISRC& ISRC)
{
	os << "ISRC:" << std::endl;

	os << "\tID: " << ISRC.ID() << std::endl;

	if (ISRC.RecordingList())
		os << *ISRC.RecordingList() << std::endl;

	return os;
}

