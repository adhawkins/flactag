#include "Disc.h"

#include "Release.h"

MusicBrainzADH::CDisc::CDisc(const XMLNode& Node)
:	m_ReleaseList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Disc node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		if (Node.isAttributeSet("id"))			
			m_ID=Node.getAttribute("id");
		
		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();
			
			if ("sectors"==NodeName)
			{
				m_Sectors=NodeValue;
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else
			{
				std::cerr << "Unrecognised disc node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CDisc::CDisc(const CDisc& Other)
:	m_ReleaseList(0)
{
	*this=Other;
}

MusicBrainzADH::CDisc& MusicBrainzADH::CDisc::operator =(const CDisc& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Sectors=Other.m_Sectors;
		
		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);
	}
	
	return *this;
}

MusicBrainzADH::CDisc::~CDisc()
{
	Cleanup();
}

void MusicBrainzADH::CDisc::Cleanup()
{
	delete m_ReleaseList;
	m_ReleaseList=0;
}

std::string MusicBrainzADH::CDisc::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CDisc::Sectors() const
{
	return m_Sectors;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> *MusicBrainzADH::CDisc::ReleaseList() const
{
	return m_ReleaseList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CDisc& Disc)
{
	os << "Disc:" << std::endl;
		
	os << "\tID:      " << Disc.ID() << std::endl;
	os << "\tSectors: " << Disc.Sectors() << std::endl;
		
	if (Disc.ReleaseList())
		os << *Disc.ReleaseList() << std::endl;
		
	return os;
}
