#include "FreeDBDisc.h"

#include "NoneMBTrack.h"

MusicBrainzADH::CFreeDBDisc::CFreeDBDisc(const XMLNode& Node)
:	m_NoneMBTrackList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "FreeDBDisc node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			else if ("artist"==NodeName)
			{
				m_Artist=NodeValue;
			}
			else if ("category"==NodeName)
			{
				m_Category=NodeValue;
			}
			else if ("year"==NodeName)
			{
				m_Year=NodeValue;
			}
			else if ("nonmb-track-list"==NodeName)
			{
				m_NoneMBTrackList=new CGenericList<CNoneMBTrack>(ChildNode,"track");
			}
			else
			{
				std::cerr << "Unrecognised cd stub node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CFreeDBDisc::CFreeDBDisc(const CFreeDBDisc& Other)
:	m_NoneMBTrackList(0)
{
	*this=Other;
}

MusicBrainzADH::CFreeDBDisc& MusicBrainzADH::CFreeDBDisc::operator =(const CFreeDBDisc& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Title=Other.m_Title;
		m_Artist=Other.m_Artist;
		m_Category=Other.m_Category;
		m_Year=Other.m_Year;
		
		if (Other.m_NoneMBTrackList)
			m_NoneMBTrackList=new CGenericList<CNoneMBTrack>(*Other.m_NoneMBTrackList);
	}
	
	return *this;
}

MusicBrainzADH::CFreeDBDisc::~CFreeDBDisc()
{
	Cleanup();
}

void MusicBrainzADH::CFreeDBDisc::Cleanup()
{
	delete m_NoneMBTrackList;
	m_NoneMBTrackList=0;
}

std::string MusicBrainzADH::CFreeDBDisc::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CFreeDBDisc::Title() const
{
	return m_Title;
}

std::string MusicBrainzADH::CFreeDBDisc::Artist() const
{
	return m_Artist;
}

std::string MusicBrainzADH::CFreeDBDisc::Category() const
{
	return m_Category;
}

std::string MusicBrainzADH::CFreeDBDisc::Year() const
{
	return m_Year;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CNoneMBTrack> *MusicBrainzADH::CFreeDBDisc::NoneMBTrackList() const
{
	return m_NoneMBTrackList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CFreeDBDisc& FreeDBDisc)
{
	os << "FreeDBDisc:" << std::endl;
		
	os << "\tID:       " << FreeDBDisc.ID() << std::endl;
	os << "\tTitle:    " << FreeDBDisc.Title() << std::endl;
	os << "\tArtist:   " << FreeDBDisc.Artist() << std::endl;
	os << "\tCategory: " << FreeDBDisc.Category() << std::endl;
	os << "\tYear:     " << FreeDBDisc.Year() << std::endl;

	if (FreeDBDisc.NoneMBTrackList())
		os << *FreeDBDisc.NoneMBTrackList() << std::endl;
		
	return os;
}
