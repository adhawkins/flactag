#include "Work.h"

#include "ArtistCredit.h"
#include "Alias.h"
#include "Relation.h"
#include "Tag.h"
#include "UserTag.h"
#include "Rating.h"
#include "UserRating.h"

MusicBrainzADH::CWork::CWork(const XMLNode& Node)
:	m_ArtistCredit(0),
	m_AliasList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Work node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=new CArtistCredit(ChildNode);
			}
			else if ("iswc"==NodeName)
			{
				m_ISWC=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("alias-list"==NodeName)
			{
				m_AliasList=new CGenericList<CAlias>(ChildNode,"alias");
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
				std::cerr << "Unrecognised work node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CWork::CWork(const CWork& Other)
:	m_ArtistCredit(0),
	m_AliasList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	*this=Other;
}

MusicBrainzADH::CWork& MusicBrainzADH::CWork::operator =(const CWork& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Type=Other.m_Type;
		m_Title=Other.m_Title;
		
		if (Other.m_ArtistCredit)
			m_ArtistCredit=new CArtistCredit(*Other.m_ArtistCredit);
				
		m_ISWC=Other.m_ISWC;
		m_Disambiguation=Other.m_Disambiguation;
		
		if (Other.m_AliasList)
			m_AliasList=new CGenericList<CAlias>(*Other.m_AliasList);
		
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

MusicBrainzADH::CWork::~CWork()
{
	Cleanup();
}

void MusicBrainzADH::CWork::Cleanup()
{
	delete m_ArtistCredit;
	m_ArtistCredit=0;
	
	delete m_AliasList;
	m_AliasList=0;
	
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

std::string MusicBrainzADH::CWork::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CWork::Type() const
{
	return m_Type;
}

std::string MusicBrainzADH::CWork::Title() const
{
	return m_Title;
}

MusicBrainzADH::CArtistCredit *MusicBrainzADH::CWork::ArtistCredit() const
{
	return m_ArtistCredit;
}

std::string MusicBrainzADH::CWork::ISWC() const
{
	return m_ISWC;
}

std::string MusicBrainzADH::CWork::Disambiguation() const
{
	return m_Disambiguation;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CAlias> *MusicBrainzADH::CWork::AliasList() const
{
	return m_AliasList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelation> *MusicBrainzADH::CWork::RelationList() const
{
	return m_RelationList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CTag> *MusicBrainzADH::CWork::TagList() const
{
	return m_TagList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CUserTag> *MusicBrainzADH::CWork::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainzADH::CRating *MusicBrainzADH::CWork::Rating() const
{
	return m_Rating;
}

MusicBrainzADH::CUserRating *MusicBrainzADH::CWork::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CWork& Work)
{
	os << "Work:" << std::endl;
		
	os << "\tID:             " << Work.ID() << std::endl;
	os << "\tWork:           " << Work.Type() << std::endl;
	os << "\tTitle:          " << Work.Title() << std::endl;
	if (Work.ArtistCredit())
		os << Work.ArtistCredit() << std::endl;
	os << "\tISWC:           " << Work.ISWC() << std::endl;
			
	os << "\tDisambiguation: " << Work.Disambiguation() << std::endl;
	if (Work.AliasList())
		os << Work.AliasList() << std::endl;
			
	if (Work.RelationList())
		os << Work.RelationList() << std::endl;
			
	if (Work.TagList())
		os << Work.TagList() << std::endl;
			
	if (Work.UserTagList())
		os << Work.UserTagList() << std::endl;
	
	if (Work.Rating())
		os << Work.Rating() << std::endl;
	
	if (Work.UserRating())
		os << Work.UserRating() << std::endl;
		
	return os;
}

