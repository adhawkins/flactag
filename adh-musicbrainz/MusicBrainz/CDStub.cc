#include "CDStub.h"

#include "NoneMBTrack.h"

MusicBrainzADH::CCDStub::CCDStub(const XMLNode& Node)
:	m_NoneMBTrackList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "CDStub node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			else if ("barcode"==NodeName)
			{
				m_Barcode=NodeValue;
			}
			else if ("comment"==NodeName)
			{
				m_Comment=NodeValue;
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

MusicBrainzADH::CCDStub::CCDStub(const CCDStub& Other)
:	m_NoneMBTrackList(0)
{
	*this=Other;
}

MusicBrainzADH::CCDStub& MusicBrainzADH::CCDStub::operator =(const CCDStub& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Title=Other.m_Title;
		m_Artist=Other.m_Artist;
		m_Barcode=Other.m_Barcode;
		m_Comment=Other.m_Comment;
		
		if (Other.m_NoneMBTrackList)
			m_NoneMBTrackList=new CGenericList<CNoneMBTrack>(*Other.m_NoneMBTrackList);
	}
	
	return *this;
}

MusicBrainzADH::CCDStub::~CCDStub()
{
	Cleanup();
}

void MusicBrainzADH::CCDStub::Cleanup()
{
	delete m_NoneMBTrackList;
	m_NoneMBTrackList=0;
}

std::string MusicBrainzADH::CCDStub::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CCDStub::Title() const
{
	return m_Title;
}

std::string MusicBrainzADH::CCDStub::Artist() const
{
	return m_Artist;
}

std::string MusicBrainzADH::CCDStub::Barcode() const
{
	return m_Barcode;
}

std::string MusicBrainzADH::CCDStub::Comment() const
{
	return m_Comment;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CNoneMBTrack> *MusicBrainzADH::CCDStub::NoneMBTrackList() const
{
	return m_NoneMBTrackList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CCDStub& CDStub)
{
	os << "CDStub:" << std::endl;
		
	os << "\tID:      " << CDStub.ID() << std::endl;
	os << "\tTitle:   " << CDStub.Title() << std::endl;
	os << "\tArtist:  " << CDStub.Artist() << std::endl;
	os << "\tBarcode: " << CDStub.Barcode() << std::endl;
	os << "\tComment: " << CDStub.Comment() << std::endl;
		
	if (CDStub.NoneMBTrackList())
		os << *CDStub.NoneMBTrackList() << std::endl;
		
	return os;
}