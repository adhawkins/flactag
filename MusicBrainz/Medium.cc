#include "Medium.h"

#include <sstream>

#include "Disc.h"
#include "Track.h"

MusicBrainzADH::CMedium::CMedium(const XMLNode& Node)
:	m_DiscList(0),
	m_TrackList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			else if ("position"==NodeName)
			{
				std::stringstream os;
				os << NodeValue;
				os >> m_Position;
			}
			else if ("format"==NodeName)
			{
				m_Format=NodeValue;
			}
			else if ("disc-list"==NodeName)
			{
				m_DiscList=new CGenericList<CDisc>(ChildNode,"disc");
			}
			else if ("track-list"==NodeName)
			{
				m_TrackList=new CGenericList<CTrack>(ChildNode,"track");
			}
			else
			{
				std::cerr << "Unrecognised medium node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CMedium::CMedium(const CMedium& Other)
:	m_DiscList(0),
	m_TrackList(0)
{
	*this=Other;
}

MusicBrainzADH::CMedium& MusicBrainzADH::CMedium::operator =(const CMedium& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_Title=Other.m_Title;
		m_Position=Other.m_Position;
		m_Format=Other.m_Format;
		
		if (Other.m_DiscList)
			m_DiscList=new CGenericList<CDisc>(*Other.m_DiscList);
		
		if (Other.m_TrackList)
			m_TrackList=new CGenericList<CTrack>(*Other.m_TrackList);
	}
	
	return *this;
}

MusicBrainzADH::CMedium::~CMedium()
{
	Cleanup();
}

void MusicBrainzADH::CMedium::Cleanup()
{
	delete m_DiscList;
	m_DiscList=0;
	
	delete m_TrackList;
	m_TrackList=0;
}

std::string MusicBrainzADH::CMedium::Title() const
{
	return m_Title;
}

int MusicBrainzADH::CMedium::Position() const
{
	return m_Position;
}

std::string MusicBrainzADH::CMedium::Format() const
{
	return m_Format;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CDisc> *MusicBrainzADH::CMedium::DiscList() const
{
	return m_DiscList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CTrack> *MusicBrainzADH::CMedium::TrackList() const
{
	return m_TrackList;
}

bool MusicBrainzADH::CMedium::ContainsDiscID(const std::string& DiscID) const
{
	bool RetVal=false;
	
	std::vector<CDisc> DiscList=m_DiscList->Items();
	std::vector<CDisc>::const_iterator ThisDisc=DiscList.begin();
	while (!RetVal && ThisDisc!=DiscList.end())
	{
		CDisc Disc=*ThisDisc;
		
		if (Disc.ID()==DiscID)
			RetVal=true;
			
		++ThisDisc;
	}
	
	return RetVal;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CMedium& Medium)
{
	os << "Medium:" << std::endl;
		
	os << "\tTitle:    " << Medium.Title() << std::endl;
	os << "\tPosition: " << Medium.Position() << std::endl;
	os << "\tFormat:   " << Medium.Format() << std::endl;
		
	if (Medium.DiscList())
		os << *Medium.DiscList() << std::endl;
			
	if (Medium.TrackList())
		os << *Medium.TrackList() << std::endl;
		
	return os;
}
