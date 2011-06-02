#include "Label.h"

#include <iostream>

#include "Lifespan.h"
#include "Rating.h"
#include "UserRating.h"
#include "Alias.h"
#include "Release.h"
#include "Relation.h"
#include "Tag.h"
#include "UserTag.h"

MusicBrainzADH::CLabel::CLabel(const XMLNode& Node)
:	m_Lifespan(0),
	m_AliasList(0),
	m_ReleaseList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			
			if ("name"==NodeName)
			{
				m_Name=NodeValue;
			}
			else if ("sort-name"==NodeName)
			{
				m_SortName=NodeValue;
			}
			else if ("label-code"==NodeName)
			{
				m_LabelCode=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("country"==NodeName)
			{
				m_Country=NodeValue;
			}
			else if ("life-span"==NodeName)
			{
				m_Lifespan=new CLifespan(ChildNode);
			}
			else if ("alias-list"==NodeName)
			{
				m_AliasList=new CGenericList<CAlias>(ChildNode,"alias");
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
				std::cerr << "Unrecognised label node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CLabel::CLabel(const CLabel& Other)
:	m_Lifespan(0),
	m_AliasList(0),
	m_ReleaseList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	*this=Other;
}

MusicBrainzADH::CLabel& MusicBrainzADH::CLabel::operator =(const CLabel& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Type=Other.m_Type;
		m_Name=Other.m_Name;
		m_SortName=Other.m_SortName;
		m_LabelCode=Other.m_LabelCode;
		m_Disambiguation=Other.m_Disambiguation;
		m_Country=Other.m_Country;
		
		if (Other.m_Lifespan)
			m_Lifespan=new CLifespan(*Other.m_Lifespan);
		
		if (Other.m_AliasList)
			m_AliasList=new CGenericList<CAlias>(*Other.m_AliasList);
		
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

MusicBrainzADH::CLabel::~CLabel()
{
	Cleanup();
}

void MusicBrainzADH::CLabel::Cleanup()
{
	delete m_Lifespan;
	m_Lifespan=0;
	
	delete m_AliasList;
	m_AliasList=0;
	
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

std::string MusicBrainzADH::CLabel::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CLabel::Type() const
{
	return m_Type;
}

std::string MusicBrainzADH::CLabel::Name() const
{
	return m_Name;
}

std::string MusicBrainzADH::CLabel::SortName() const
{
	return m_SortName;
}

std::string MusicBrainzADH::CLabel::LabelCode() const
{
	return m_LabelCode;
}

std::string MusicBrainzADH::CLabel::Disambiguation() const
{
	return m_Disambiguation;
}

std::string MusicBrainzADH::CLabel::Country() const
{
	return m_Country;
}

MusicBrainzADH::CLifespan *MusicBrainzADH::CLabel::Lifespan() const
{
	return m_Lifespan;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CAlias> *MusicBrainzADH::CLabel::AliasList() const
{
	return m_AliasList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> *MusicBrainzADH::CLabel::ReleaseList() const
{
	return m_ReleaseList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelation> *MusicBrainzADH::CLabel::RelationList() const
{
	return m_RelationList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CTag> *MusicBrainzADH::CLabel::TagList() const
{
	return m_TagList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CUserTag> *MusicBrainzADH::CLabel::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainzADH::CRating *MusicBrainzADH::CLabel::Rating() const
{
	return m_Rating;
}

MusicBrainzADH::CUserRating *MusicBrainzADH::CLabel::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CLabel& Label)
{
	os << "Label:" << std::endl;
		
	os << "\tID:             " << Label.ID() << std::endl;
	os << "\tType:           " << Label.Type() << std::endl;
	os << "\tName:           " << Label.Name() << std::endl;
	os << "\tSort name:      " << Label.SortName() << std::endl;
	os << "\tLabel code:     " << Label.LabelCode() << std::endl;
	os << "\tDisambiguation: " << Label.Disambiguation() << std::endl;
	os << "\tCountry:        " << Label.Country() << std::endl;
		
	if (Label.Lifespan())
		os << *Label.Lifespan() << std::endl;
		
	if (Label.AliasList())
		os << *Label.AliasList() << std::endl;
		
	if (Label.ReleaseList())
		os << *Label.ReleaseList() << std::endl;
		
	if (Label.RelationList())
		os << *Label.RelationList() << std::endl;
		
	if (Label.TagList())
		os << *Label.TagList() << std::endl;
		
	if (Label.UserTagList())
		os << *Label.UserTagList() << std::endl;
		
	if (Label.Rating())
		os << *Label.Rating() << std::endl;
		
	if (Label.UserRating())
		os << *Label.UserRating() << std::endl;
		
	return os;
}
	
