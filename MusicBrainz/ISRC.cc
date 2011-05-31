#include "ISRC.h"

MusicBrainzADH::CISRC::CISRC(const XMLNode& Node)
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

MusicBrainzADH::CISRC::CISRC(const CISRC& Other)
:	m_RecordingList(0)
{
	*this=Other;
}

MusicBrainzADH::CISRC& MusicBrainzADH::CISRC::operator =(const CISRC& Other)
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

MusicBrainzADH::CISRC::~CISRC()
{
	Cleanup();
}

void MusicBrainzADH::CISRC::Cleanup()
{
	delete m_RecordingList;
	m_RecordingList=0;
}

std::string MusicBrainzADH::CISRC::ID() const
{
	return m_ID;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRecording> *MusicBrainzADH::CISRC::RecordingList() const
{
	return m_RecordingList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CISRC& ISRC)
{
	os << "ISRC:" << std::endl;
		
	os << "\tID: " << ISRC.ID() << std::endl;
		
	if (ISRC.RecordingList())
		os << *ISRC.RecordingList() << std::endl;
		
	return os;
}
	
