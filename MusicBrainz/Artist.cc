#include "Artist.h"

#include "Lifespan.h"
#include "Rating.h"
#include "UserRating.h"
#include "Alias.h"
#include "Recording.h"
#include "Release.h"
#include "ReleaseGroup.h"
#include "Label.h"
#include "Work.h"
#include "Relation.h"
#include "Tag.h"
#include "UserTag.h"

MusicBrainzADH::CArtist::CArtist(const XMLNode& Node)
:	m_Lifespan(0),
	m_AliasList(0),
	m_RecordingList(0),
	m_ReleaseList(0),
	m_ReleaseGroupList(0),
	m_LabelList(0),
	m_WorkList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Artist node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			else if ("gender"==NodeName)
			{
				m_Gender=NodeValue;
			}
			else if ("country"==NodeName)
			{
				m_Country=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("life-span"==NodeName)
			{
				m_Lifespan=new CLifespan(ChildNode);
			}
			else if ("alias-list"==NodeName)
			{
				m_AliasList=new CGenericList<CAlias>(ChildNode,"alias");
			}
			else if ("recording-list"==NodeName)
			{
				m_RecordingList=new CGenericList<CRecording>(ChildNode,"recording");
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else if ("release-group-list"==NodeName)
			{
				m_ReleaseGroupList=new CGenericList<CReleaseGroup>(ChildNode,"release");
			}
			else if ("label-list"==NodeName)
			{
				m_LabelList=new CGenericList<CLabel>(ChildNode,"label");
			}
			else if ("work-list"==NodeName)
			{
				m_WorkList=new CGenericList<CWork>(ChildNode,"work");
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
				std::cerr << "Unrecognised artist node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CArtist::CArtist(const CArtist& Other)
:	m_Lifespan(0),
	m_AliasList(0),
	m_RecordingList(0),
	m_ReleaseList(0),
	m_ReleaseGroupList(0),
	m_LabelList(0),
	m_WorkList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	*this=Other;
}

MusicBrainzADH::CArtist::CArtist& MusicBrainzADH::CArtist::operator =(const CArtist& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Type=Other.m_Type;
		m_Name=Other.m_Name;
		m_SortName=Other.m_SortName;
		m_Gender=Other.m_Gender;
		m_Country=Other.m_Country;
		m_Disambiguation=Other.m_Disambiguation;
		
		if (Other.m_Lifespan)
			m_Lifespan=new CLifespan(*Other.m_Lifespan);
		
		if (Other.m_AliasList)
			m_AliasList=new CGenericList<CAlias>(*Other.m_AliasList);
		
		if (Other.m_RecordingList)
			m_RecordingList=new CGenericList<CRecording>(*Other.m_RecordingList);
		
		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);
		
		if (Other.m_ReleaseGroupList)
			m_ReleaseGroupList=new CGenericList<CReleaseGroup>(*Other.m_ReleaseGroupList);
		
		if (Other.m_LabelList)
			m_LabelList=new CGenericList<CLabel>(*Other.m_LabelList);
		
		if (Other.m_WorkList)
			m_WorkList=new CGenericList<CWork>(*Other.m_WorkList);
		
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

MusicBrainzADH::CArtist::~CArtist()
{
	Cleanup();
}

void MusicBrainzADH::CArtist::Cleanup()
{
	delete m_Lifespan;
	m_Lifespan=0;
	
	delete m_AliasList;
	m_AliasList=0;
	
	delete m_RecordingList;
	m_RecordingList=0;
	
	delete m_ReleaseList;
	m_ReleaseList=0;
	
	delete m_ReleaseGroupList;
	m_ReleaseGroupList=0;
	
	delete m_LabelList;
	m_LabelList=0;
	
	delete m_WorkList;
	m_WorkList=0;
	
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

std::string MusicBrainzADH::CArtist::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CArtist::Type() const
{
	return m_Type;
}

std::string MusicBrainzADH::CArtist::Name() const
{
	return m_Name;
}

std::string MusicBrainzADH::CArtist::SortName() const
{
	return m_SortName;
}

std::string MusicBrainzADH::CArtist::Gender() const
{
	return m_Gender;
}

std::string MusicBrainzADH::CArtist::Country() const
{
	return m_Country;
}

std::string MusicBrainzADH::CArtist::Disambiguation() const
{
	return m_Disambiguation;
}

MusicBrainzADH::CLifespan *MusicBrainzADH::CArtist::Lifespan() const
{
	return m_Lifespan;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CAlias> *MusicBrainzADH::CArtist::AliasList() const
{
	return m_AliasList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRecording> *MusicBrainzADH::CArtist::RecordingList() const
{
	return m_RecordingList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> *MusicBrainzADH::CArtist::ReleaseList() const
{
	return m_ReleaseList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CReleaseGroup> *MusicBrainzADH::CArtist::ReleaseGroupList() const
{
	return m_ReleaseGroupList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CLabel> *MusicBrainzADH::CArtist::LabelList() const
{
	return m_LabelList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CWork> *MusicBrainzADH::CArtist::WorkList() const
{
	return m_WorkList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelation> *MusicBrainzADH::CArtist::RelationList() const
{
	return m_RelationList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CTag> *MusicBrainzADH::CArtist::TagList() const
{
	return m_TagList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CUserTag> *MusicBrainzADH::CArtist::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainzADH::CRating *MusicBrainzADH::CArtist::Rating() const
{
	return m_Rating;
}

MusicBrainzADH::CUserRating *MusicBrainzADH::CArtist::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CArtist& Artist)
{
	os << "Artist:" << std::endl;
		
	os << "\tID:             " << Artist.ID() << std::endl;
	os << "\tType:           " << Artist.Type() << std::endl;
	os << "\tName:           " << Artist.Name() << std::endl;
	os << "\tSort name:      " << Artist.SortName() << std::endl;
	os << "\tGender:         " << Artist.Gender() << std::endl;
	os << "\tCountry:        " << Artist.Country() << std::endl;
	os << "\tDisambiguation: " << Artist.Disambiguation() << std::endl;
	
	if (Artist.Lifespan())
		os << *Artist.Lifespan() << std::endl;
	
	if (Artist.AliasList())
		os << *Artist.AliasList() << std::endl;
	
	if (Artist.RecordingList())
		os << *Artist.RecordingList() << std::endl;
	
	if (Artist.ReleaseList())
		os << *Artist.ReleaseList() << std::endl;
	
	if (Artist.ReleaseGroupList())
		os << *Artist.ReleaseGroupList() << std::endl;
	
	if (Artist.LabelList())
		os << *Artist.LabelList() << std::endl;
	
	if (Artist.WorkList())
		os << *Artist.WorkList() << std::endl;
	
	if (Artist.RelationList())
		os << *Artist.RelationList() << std::endl;
	
	if (Artist.TagList())
		os << *Artist.TagList() << std::endl;
	
	if (Artist.UserTagList())
		os << *Artist.UserTagList() << std::endl;
	
	if (Artist.Rating())
		os << *Artist.Rating() << std::endl;
	
	if (Artist.UserRating())
		os << *Artist.UserRating() << std::endl;

	return os;
}
	
