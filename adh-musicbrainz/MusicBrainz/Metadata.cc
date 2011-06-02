#include "Metadata.h"

#include "Artist.h"
#include "Release.h"
#include "ReleaseGroup.h"
#include "Recording.h"
#include "Label.h"
#include "Work.h"
#include "PUID.h"
#include "ISRC.h"
#include "Disc.h"
#include "Rating.h"
#include "UserRating.h"
#include "Collection.h"
#include "Annotation.h"
#include "CDStub.h"
#include "FreeDBDisc.h"
#include "Tag.h"
#include "UserTag.h"
#include "LabelInfo.h"

MusicBrainzADH::CMetadata::CMetadata(const XMLNode& Node)
:	m_Artist(0),
	m_Release(0),
	m_ReleaseGroup(0),
	m_Recording(0),
	m_Label(0),
	m_Work(0),
	m_PUID(0),
	m_ISRC(0),
	m_Disc(0),
	m_LabelInfoList(0),
	m_Rating(0),
	m_UserRating(0),
	m_Collection(0),
	m_ArtistList(0),
	m_ReleaseList(0),
	m_ReleaseGroupList(0),
	m_RecordingList(0),
	m_LabelList(0),
	m_WorkList(0),
	m_ISRCList(0),
	m_AnnotationList(0),
	m_CDStubList(0),
	m_FreeDBDiscList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_CollectionList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Metadata node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		if (Node.isAttributeSet("generator"))			
			m_Generator=Node.getAttribute("generator");
		
		if (Node.isAttributeSet("created"))			
			m_Created=Node.getAttribute("created");
		
		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();
			
			if ("artist"==NodeName)
			{
				m_Artist=new CArtist(ChildNode);
			}
			else if ("release"==NodeName)
			{
				m_Release=new CRelease(ChildNode);
			}
			else if ("release-group"==NodeName)
			{
				m_ReleaseGroup=new CReleaseGroup(ChildNode);
			}
			else if ("recording"==NodeName)
			{
				m_Recording=new CRecording(ChildNode);
			}
			else if ("label"==NodeName)
			{
				m_Label=new CLabel(ChildNode);
			}
			else if ("work"==NodeName)
			{
				m_Work=new CWork(ChildNode);
			}
			else if ("puid"==NodeName)
			{
				m_PUID=new CPUID(ChildNode);
			}
			else if ("isrc"==NodeName)
			{
				m_ISRC=new CISRC(ChildNode);
			}
			else if ("disc"==NodeName)
			{
				m_Disc=new CDisc(ChildNode);
			}
			else if ("rating"==NodeName)
			{
				m_Rating=new CRating(ChildNode);
			}
			else if ("user-rating"==NodeName)
			{
				m_UserRating=new CUserRating(ChildNode);
			}
			else if ("collection"==NodeName)
			{
				m_Collection=new CCollection(ChildNode);
			}
			else if ("artist-list"==NodeName)
			{
				m_ArtistList=new CGenericList<CArtist>(ChildNode,"artist");
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else if ("release-group-list"==NodeName)
			{
				m_ReleaseGroupList=new CGenericList<CReleaseGroup>(ChildNode,"release-group");
			}
			else if ("recording-list"==NodeName)
			{
				m_RecordingList=new CGenericList<CRecording>(ChildNode,"recording");
			}
			else if ("label-list"==NodeName)
			{
				m_LabelList=new CGenericList<CLabel>(ChildNode,"label");
			}
			else if ("work-list"==NodeName)
			{
				m_WorkList=new CGenericList<CWork>(ChildNode,"work");
			}
			else if ("isrc-list"==NodeName)
			{
				m_ISRCList=new CGenericList<CISRC>(ChildNode,"isrc");
			}
			else if ("annotation-list"==NodeName)
			{
				m_AnnotationList=new CGenericList<CAnnotation>(ChildNode,"annotation");
			}
			else if ("cdstub-list"==NodeName)
			{
				m_CDStubList=new CGenericList<CCDStub>(ChildNode,"ctstub");
			}
			else if ("freedb-disc-list"==NodeName)
			{
				m_FreeDBDiscList=new CGenericList<CFreeDBDisc>(ChildNode,"freedb-disc");
			}
			else if ("tag-list"==NodeName)
			{
				m_TagList=new CGenericList<CTag>(ChildNode,"tag");
			}
			else if ("user-tag-list"==NodeName)
			{
				m_UserTagList=new CGenericList<CUserTag>(ChildNode,"user-tag");
			}
			else if ("collection-list"==NodeName)
			{
				m_CollectionList=new CGenericList<CCollection>(ChildNode,"collection");
			}
			else
			{
				std::cerr << "Unrecognised metadata node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CMetadata::CMetadata(const CMetadata& Other)
:	m_Artist(0),
	m_Release(0),
	m_ReleaseGroup(0),
	m_Recording(0),
	m_Label(0),
	m_Work(0),
	m_PUID(0),
	m_ISRC(0),
	m_Disc(0),
	m_LabelInfoList(0),
	m_Rating(0),
	m_UserRating(0),
	m_Collection(0),
	m_ArtistList(0),
	m_ReleaseList(0),
	m_ReleaseGroupList(0),
	m_RecordingList(0),
	m_LabelList(0),
	m_WorkList(0),
	m_ISRCList(0),
	m_AnnotationList(0),
	m_CDStubList(0),
	m_FreeDBDiscList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_CollectionList(0)
{
	*this=Other;
}

MusicBrainzADH::CMetadata& MusicBrainzADH::CMetadata::operator =(const CMetadata& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_Generator=Other.m_Generator;
		m_Created=Other.m_Created;
		
		if (Other.m_Artist)
			m_Artist=new CArtist(*Other.m_Artist);
		
		if (Other.m_Release)
			m_Release=new CRelease(*Other.m_Release);
		
		if (Other.m_ReleaseGroup)
			m_ReleaseGroup=new CReleaseGroup(*Other.m_ReleaseGroup);
		
		if (Other.m_Recording)
			m_Recording=new CRecording(*Other.m_Recording);
		
		if (Other.m_Label)
			m_Label=new CLabel(*Other.m_Label);
		
		if (Other.m_Work)
			m_Work=new CWork(*Other.m_Work);
		
		if (Other.m_PUID)
			m_PUID=new CPUID(*Other.m_PUID);
		
		if (Other.m_ISRC)
			m_ISRC=new CISRC(*Other.m_ISRC);
		
		if (Other.m_Disc)
			m_Disc=new CDisc(*Other.m_Disc);
		
		if (Other.m_LabelInfoList)
			m_LabelInfoList=new CGenericList<CLabelInfo>(*Other.m_LabelInfoList);
		
		if (Other.m_Rating)
			m_Rating=new CRating(*Other.m_Rating);
		
		if (Other.m_UserRating)
			m_UserRating=new CUserRating(*Other.m_UserRating);
		
		if (Other.m_Collection)
			m_Collection=new CCollection(*Other.m_Collection);
		
		if (Other.m_ArtistList)
			m_ArtistList=new CGenericList<CArtist>(*Other.m_ArtistList);
		
		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);
		
		if (Other.m_ReleaseGroupList)
			m_ReleaseGroupList=new CGenericList<CReleaseGroup>(*Other.m_ReleaseGroupList);
		
		if (Other.m_RecordingList)
			m_RecordingList=new CGenericList<CRecording>(*Other.m_RecordingList);
		
		if (Other.m_LabelList)
			m_LabelList=new CGenericList<CLabel>(*Other.m_LabelList);
		
		if (Other.m_WorkList)
			m_WorkList=new CGenericList<CWork>(*Other.m_WorkList);
		
		if (Other.m_ISRCList)
			m_ISRCList=new CGenericList<CISRC>(*Other.m_ISRCList);
		
		if (Other.m_AnnotationList)
			m_AnnotationList=new CGenericList<CAnnotation>(*Other.m_AnnotationList);
		
		if (Other.m_CDStubList)
			m_CDStubList=new CGenericList<CCDStub>(*Other.m_CDStubList);
		
		if (Other.m_FreeDBDiscList)
			m_FreeDBDiscList=new CGenericList<CFreeDBDisc>(*Other.m_FreeDBDiscList);
		
		if (Other.m_TagList)
			m_TagList=new CGenericList<CTag>(*Other.m_TagList);
		
		if (Other.m_UserTagList)
			m_UserTagList=new CGenericList<CUserTag>(*Other.m_UserTagList);
		
		if (Other.m_CollectionList)
			m_CollectionList=new CGenericList<CCollection>(*Other.m_CollectionList);
	}
	
	return *this;
}

MusicBrainzADH::CMetadata::~CMetadata()
{
	Cleanup();
}

void MusicBrainzADH::CMetadata::Cleanup()
{
	delete m_Artist;
	m_Artist=0;
	
	delete m_Release;
	m_Release=0;
	
	delete m_ReleaseGroup;
	m_ReleaseGroup=0;
	
	delete m_Recording;
	m_Recording=0;
	
	delete m_Label;
	m_Label=0;
	
	delete m_Work;
	m_Work=0;
	
	delete m_PUID;
	m_PUID=0;
	
	delete m_ISRC;
	m_ISRC=0;
	
	delete m_Disc;
	m_Disc=0;
	
	delete m_LabelInfoList;
	m_LabelInfoList=0;
	
	delete m_Rating;
	m_Rating=0;
	
	delete m_UserRating;
	m_UserRating=0;
	
	delete m_Collection;
	m_Collection=0;
	
	delete m_ArtistList;
	m_ArtistList=0;
	
	delete m_ReleaseList;
	m_ReleaseList=0;
	
	delete m_ReleaseGroupList;
	m_ReleaseGroupList=0;
	
	delete m_RecordingList;
	m_RecordingList=0;
	
	delete m_LabelList;
	m_LabelList=0;
	
	delete m_WorkList;
	m_WorkList=0;
	
	delete m_ISRCList;
	m_ISRCList=0;
	
	delete m_AnnotationList;
	m_AnnotationList=0;
	
	delete m_CDStubList;
	m_CDStubList=0;
	
	delete m_FreeDBDiscList;
	m_FreeDBDiscList=0;
	
	delete m_TagList;
	m_TagList=0;
	
	delete m_UserTagList;
	m_UserTagList=0;
	
	delete m_CollectionList;
	m_CollectionList=0;
}

std::string MusicBrainzADH::CMetadata::Generator() const
{
	return m_Generator;
}

std::string MusicBrainzADH::CMetadata::Created() const
{
	return m_Created;
}

MusicBrainzADH::CArtist *MusicBrainzADH::CMetadata::Artist() const
{
	return m_Artist;
}

MusicBrainzADH::CRelease *MusicBrainzADH::CMetadata::Release() const
{
	return m_Release;
}

MusicBrainzADH::CReleaseGroup *MusicBrainzADH::CMetadata::ReleaseGroup() const
{
	return m_ReleaseGroup;
}

MusicBrainzADH::CRecording *MusicBrainzADH::CMetadata::Recording() const
{
	return m_Recording;
}

MusicBrainzADH::CLabel *MusicBrainzADH::CMetadata::Label() const
{
	return m_Label;
}

MusicBrainzADH::CWork *MusicBrainzADH::CMetadata::Work() const
{
	return m_Work;
}

MusicBrainzADH::CPUID *MusicBrainzADH::CMetadata::PUID() const
{
	return m_PUID;
}

MusicBrainzADH::CISRC *MusicBrainzADH::CMetadata::ISRC() const
{
	return m_ISRC;
}

MusicBrainzADH::CDisc *MusicBrainzADH::CMetadata::Disc() const
{
	return m_Disc;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CLabelInfo> *MusicBrainzADH::CMetadata::LabelInfoList() const
{
	return m_LabelInfoList;
}

MusicBrainzADH::CUserRating *MusicBrainzADH::CMetadata::UserRating() const
{
	return m_UserRating;
}

MusicBrainzADH::CCollection *MusicBrainzADH::CMetadata::Collection() const
{
	return m_Collection;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CArtist> *MusicBrainzADH::CMetadata::ArtistList() const
{
	return m_ArtistList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> *MusicBrainzADH::CMetadata::ReleaseList() const
{
	return m_ReleaseList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CReleaseGroup> *MusicBrainzADH::CMetadata::ReleaseGroupList() const
{
	return m_ReleaseGroupList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRecording> *MusicBrainzADH::CMetadata::RecordingList() const
{
	return m_RecordingList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CLabel> *MusicBrainzADH::CMetadata::LabelList() const
{
	return m_LabelList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CWork> *MusicBrainzADH::CMetadata::WorkList() const
{
	return m_WorkList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CISRC> *MusicBrainzADH::CMetadata::ISRCList() const
{
	return m_ISRCList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CAnnotation> *MusicBrainzADH::CMetadata::AnnotationList() const
{
	return m_AnnotationList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CCDStub> *MusicBrainzADH::CMetadata::CDStubList() const
{
	return m_CDStubList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CFreeDBDisc> *MusicBrainzADH::CMetadata::FreeDBDiscList() const
{
	return m_FreeDBDiscList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CTag> *MusicBrainzADH::CMetadata::TagList() const
{
	return m_TagList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CUserTag> *MusicBrainzADH::CMetadata::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CCollection> *MusicBrainzADH::CMetadata::CollectionList() const
{
	return m_CollectionList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CMetadata& Metadata)
{
	os << "Metadata:" << std::endl;
		
	os << Metadata.Generator() << std::endl;
	os << Metadata.Created() << std::endl;
		
	if (Metadata.Artist())
		os << *Metadata.Artist() << std::endl;
		
	if (Metadata.Release())
		os << *Metadata.Release() << std::endl;
	
	if (Metadata.ReleaseGroup())
		os << *Metadata.ReleaseGroup() << std::endl;
	
	if (Metadata.Recording())
		os << *Metadata.Recording() << std::endl;
	
	if (Metadata.Label())
		os << *Metadata.Label() << std::endl;
	
	if (Metadata.Work())
		os << *Metadata.Work() << std::endl;
	
	if (Metadata.PUID())
		os << *Metadata.PUID() << std::endl;
	
	if (Metadata.ISRC())
		os << *Metadata.ISRC() << std::endl;
	
	if (Metadata.Disc())
		os << *Metadata.Disc() << std::endl;
	
	if (Metadata.LabelInfoList())
		os << *Metadata.LabelInfoList() << std::endl;
	
	if (Metadata.UserRating())
		os << *Metadata.UserRating() << std::endl;
	
	if (Metadata.Collection())
		os << *Metadata.Collection() << std::endl;
	
	if (Metadata.ArtistList())
		os << *Metadata.ArtistList() << std::endl;
	
	if (Metadata.ReleaseList())
		os << *Metadata.ReleaseList() << std::endl;
	
	if (Metadata.ReleaseGroupList())
		os << *Metadata.ReleaseGroupList() << std::endl;
	
	if (Metadata.RecordingList())
		os << *Metadata.RecordingList() << std::endl;
	
	if (Metadata.LabelList())
		os << *Metadata.LabelList() << std::endl;
	
	if (Metadata.WorkList())
		os << *Metadata.WorkList() << std::endl;
	
	if (Metadata.ISRCList())
		os << *Metadata.ISRCList() << std::endl;
	
	if (Metadata.AnnotationList())
		os << *Metadata.AnnotationList() << std::endl;
	
	if (Metadata.CDStubList())
		os << *Metadata.CDStubList() << std::endl;
	
	if (Metadata.FreeDBDiscList())
		os << *Metadata.FreeDBDiscList() << std::endl;
	
	if (Metadata.TagList())
		os << *Metadata.TagList() << std::endl;
	
	if (Metadata.UserTagList())
		os << *Metadata.UserTagList() << std::endl;
	
	if (Metadata.CollectionList())
		os << *Metadata.CollectionList() << std::endl;

	return os;
}
