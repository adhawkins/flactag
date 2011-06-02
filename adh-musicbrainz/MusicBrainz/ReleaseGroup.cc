#include "ReleaseGroup.h"

#include "ArtistCredit.h"
#include "Rating.h"
#include "UserRating.h"
#include "Release.h"
#include "Relation.h"
#include "Tag.h"
#include "UserTag.h"

MusicBrainzADH::CReleaseGroup::CReleaseGroup(const XMLNode& Node)
:	m_ArtistCredit(0),
	m_ReleaseList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Name credit node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))			
			m_ID=Node.getAttribute("id");
		
		if (Node.isAttributeSet("type"))			
			m_Type=Node.getAttribute("type");
		
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
			else if ("comment"==NodeName)
			{
				m_Comment=NodeValue;
			}
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=new CArtistCredit(ChildNode);
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
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
				std::cerr << "Unrecognised release group node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CReleaseGroup::CReleaseGroup(const CReleaseGroup& Other)
:	m_ArtistCredit(0),
	m_ReleaseList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	*this=Other;
}

MusicBrainzADH::CReleaseGroup& MusicBrainzADH::CReleaseGroup::operator =(const CReleaseGroup& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Type=Other.m_Type;
		m_Title=Other.m_Title;
		m_Comment=Other.m_Comment;
		
		if (Other.m_ArtistCredit)
			m_ArtistCredit=new CArtistCredit(*Other.m_ArtistCredit);
		
		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);
		
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

MusicBrainzADH::CReleaseGroup::~CReleaseGroup()
{
	Cleanup();
}

void MusicBrainzADH::CReleaseGroup::Cleanup()
{
	delete m_ArtistCredit;
	m_ArtistCredit=0;
	
	delete m_ReleaseList;
	m_ReleaseList=0;
	
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

std::string MusicBrainzADH::CReleaseGroup::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CReleaseGroup::Type() const
{
	return m_Type;
}

std::string MusicBrainzADH::CReleaseGroup::Title() const
{
	return m_Title;
}

std::string MusicBrainzADH::CReleaseGroup::Comment() const
{
	return m_Comment;
}

MusicBrainzADH::CArtistCredit *MusicBrainzADH::CReleaseGroup::ArtistCredit() const
{
	return m_ArtistCredit;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> *MusicBrainzADH::CReleaseGroup::ReleaseList() const
{
	return m_ReleaseList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelation> *MusicBrainzADH::CReleaseGroup::RelationList() const
{
	return m_RelationList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CTag> *MusicBrainzADH::CReleaseGroup::TagList() const
{
	return m_TagList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CUserTag> *MusicBrainzADH::CReleaseGroup::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainzADH::CRating *MusicBrainzADH::CReleaseGroup::Rating() const
{
	return m_Rating;
}

MusicBrainzADH::CUserRating *MusicBrainzADH::CReleaseGroup::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CReleaseGroup& ReleaseGroup)
{
	os << "Release group:" << std::endl;
		
	os << "\tID:      " << ReleaseGroup.ID() << std::endl;
	os << "\tType:    " << ReleaseGroup.Type() << std::endl;
	os << "\tTitle:   " << ReleaseGroup.Title() << std::endl;
	os << "\tComment: " << ReleaseGroup.Comment() << std::endl;
		
	if (ReleaseGroup.ArtistCredit())
		os << *ReleaseGroup.ArtistCredit() << std::endl;
		
	if (ReleaseGroup.ReleaseList())
		os << *ReleaseGroup.ReleaseList() << std::endl;
		
	if (ReleaseGroup.RelationList())
		os << *ReleaseGroup.RelationList() << std::endl;
		
	if (ReleaseGroup.TagList())
		os << *ReleaseGroup.TagList() << std::endl;
		
	if (ReleaseGroup.UserTagList())
		os << *ReleaseGroup.UserTagList() << std::endl;
		
	if (ReleaseGroup.Rating())
		os << *ReleaseGroup.Rating() << std::endl;
		
	if (ReleaseGroup.UserRating())
		os << *ReleaseGroup.UserRating() << std::endl;
	
	return os;
}

