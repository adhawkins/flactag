#include "PUID.h"

MusicBrainzADH::CPUID::CPUID(const XMLNode& Node)
:	m_RecordingList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "PUID node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
				std::cerr << "Unrecognised PUID node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CPUID::CPUID(const CPUID& Other)
:	m_RecordingList(0)
{
	*this=Other;
}

MusicBrainzADH::CPUID& MusicBrainzADH::CPUID::operator =(const CPUID& Other)
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
			
MusicBrainzADH::CPUID::~CPUID()
{
	Cleanup();
}

void MusicBrainzADH::CPUID::Cleanup()
{
	delete m_RecordingList;
	m_RecordingList=0;
}

std::string MusicBrainzADH::CPUID::ID() const
{
	return m_ID;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRecording> *MusicBrainzADH::CPUID::RecordingList() const
{
	return m_RecordingList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CPUID& PUID)
{
	os << "PUID:" << std::endl;
		
	os << "\tID: " << PUID.ID() << std::endl;

	if (PUID.RecordingList())
		os << *PUID.RecordingList() << std::endl;
		
	return os;
}
	
