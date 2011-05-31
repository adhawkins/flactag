#include "Recording.h"

#include "ArtistCredit.h"
#include "Rating.h"
#include "UserRating.h"
#include "Release.h"
#include "PUID.h"
#include "ISRC.h"
#include "Relation.h"
#include "Tag.h"
#include "UserTag.h"

MusicBrainzADH::CRecording::CRecording(const XMLNode& Node)
:	m_ArtistCredit(0),
	m_ReleaseList(0),
	m_PUIDList(0),
	m_ISRCList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			else if ("length"==NodeName)
			{
				m_Length=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=new CArtistCredit(ChildNode);
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else if ("puid-list"==NodeName)
			{
				m_PUIDList=new CGenericList<CPUID>(ChildNode,"puid");
			}
			else if ("isrc-list"==NodeName)
			{
				m_ISRCList=new CGenericList<CISRC>(ChildNode,"isrc");
			}
			else if ("relation-list"==NodeName)
			{
				m_RelationList=new CGenericList<CRelation>(ChildNode,"relation");
			}
			else if ("tag-list"==NodeName)
			{
				m_TagList=new CGenericList<CTag>(ChildNode,"tag");
			}
			else if ("user-tag-list"==NodeName)
			{
				m_UserTagList=new CGenericList<CUserTag>(ChildNode,"user-tag");
			}
			else if ("rating"==NodeName)
			{
				m_Rating=new CRating(ChildNode);
			}
			else if ("user-rating"==NodeName)
			{
				m_UserRating=new CUserRating(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised recording node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CRecording::CRecording(const CRecording& Other)
:	m_ArtistCredit(0),
	m_ReleaseList(0),
	m_PUIDList(0),
	m_ISRCList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	*this=Other;
}

MusicBrainzADH::CRecording& MusicBrainzADH::CRecording::operator =(const CRecording& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Title=Other.m_Title;
		m_Length=Other.m_Length;
		m_Disambiguation=Other.m_Disambiguation;
		
		if (Other.m_ArtistCredit)
			m_ArtistCredit=new CArtistCredit(*Other.m_ArtistCredit);
		
		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);
		
		if (Other.m_PUIDList)
			m_PUIDList=new CGenericList<CPUID>(*Other.m_PUIDList);
		
		if (Other.m_ISRCList)
			m_ISRCList=new CGenericList<CISRC>(*Other.m_ISRCList);
		
		if (Other.m_RelationList)
			m_RelationList=new CGenericList<CRelation>(*Other.m_RelationList);
		
		if (Other.m_TagList)
			m_TagList=new CGenericList<CTag>(*Other.m_TagList);
		
		if (Other.m_UserTagList)
			m_UserTagList=new CGenericList<CUserTag>(*Other.m_UserTagList);
		
		if (Other.m_Rating)
			m_Rating=new CRating(*Other.m_Rating);
		
		if (Other.m_UserRating)
			m_UserRating=new CUserRating(*Other.m_UserRating);
	}
	
	return *this;
}

MusicBrainzADH::CRecording::~CRecording()
{
	Cleanup();
}

void MusicBrainzADH::CRecording::Cleanup()
{
	delete m_ArtistCredit;
	m_ArtistCredit=0;
	
	delete m_ReleaseList;
	m_ReleaseList=0;
	
	delete m_PUIDList;
	m_PUIDList=0;
	
	delete m_ISRCList;
	m_ISRCList=0;
	
	delete m_RelationList;
	m_RelationList=0;
	
	delete m_TagList;
	m_TagList=0;
	
	delete m_UserTagList;
	m_UserTagList=0;
	
	delete m_Rating;
	m_Rating=0;
	
	delete m_UserRating;
	m_UserRating=0;
}

std::string MusicBrainzADH::CRecording::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CRecording::Title() const
{
	return m_Title;
}

std::string MusicBrainzADH::CRecording::Length() const
{
	return m_Length;
}

std::string MusicBrainzADH::CRecording::Disambiguation() const
{
	return m_Disambiguation;
}

MusicBrainzADH::CArtistCredit *MusicBrainzADH::CRecording::ArtistCredit() const
{
	return m_ArtistCredit;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> *MusicBrainzADH::CRecording::ReleaseList() const
{
	return m_ReleaseList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CPUID> *MusicBrainzADH::CRecording::PUIDList() const
{
	return m_PUIDList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CISRC> *MusicBrainzADH::CRecording::ISRCList() const
{
	return m_ISRCList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelation> *MusicBrainzADH::CRecording::RelationList() const
{
	return m_RelationList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CTag> *MusicBrainzADH::CRecording::TagList() const
{
	return m_TagList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CUserTag> *MusicBrainzADH::CRecording::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainzADH::CRating *MusicBrainzADH::CRecording::Rating() const
{
	return m_Rating;
}

MusicBrainzADH::CUserRating *MusicBrainzADH::CRecording::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRecording& Recording)
{
	os << "Recording:" << std::endl;
		
	os << "\tID:             " << Recording.ID() << std::endl;
	os << "\tTitle:          " << Recording.Title() << std::endl;
	os << "\tLength:         " << Recording.Length() << std::endl;
	os << "\tDisambiguation: " << Recording.Disambiguation() << std::endl;
		
	if (Recording.ArtistCredit())
		os << *Recording.ArtistCredit() << std::endl;
		
	if (Recording.ReleaseList())
		os << *Recording.ReleaseList() << std::endl;
		
	if (Recording.PUIDList())
		os << *Recording.PUIDList() << std::endl;
		
	if (Recording.ISRCList())
		os << *Recording.ISRCList() << std::endl;
		
	if (Recording.RelationList())
		os << *Recording.RelationList() << std::endl;
		
	if (Recording.TagList())
		os << *Recording.TagList() << std::endl;
		
	if (Recording.UserTagList())
		os << *Recording.UserTagList() << std::endl;
		
	if (Recording.Rating())
		os << *Recording.Rating() << std::endl;
		
	if (Recording.UserRating())
		os << *Recording.UserRating() << std::endl;
		
	return os;
}
