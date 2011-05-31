//http://bugs.musicbrainz.org/browser/mmd-schema/trunk/schema/musicbrainz_mmd-2.0.rng
//http://wiki.musicbrainz.org/Picard_Tag_Mapping
//http://www.musicbrainz.org/ws/2/release/2bd8551b-7910-3647-a833-38b616257ed5?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits
//http://www.musicbrainz.org/ws/2/release/ae8c2094-f3a8-45f8-8c1b-09d069425526?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits
//http://www.musicbrainz.org/ws/2/release/8fd13191-2d9a-4670-b789-0c99a06278e0?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits

//Next to do is release

#include "Release.h"

#include <string.h>

#include "xmlParser/xmlParser.h"

#include "TextRepresentation.h"
#include "ArtistCredit.h"
#include "ReleaseGroup.h"
#include "Medium.h"
#include "LabelInfo.h"
#include "Relation.h"

MusicBrainzADH::CRelease::CRelease(const XMLNode& Node)
:	m_TextRepresentation(0),
	m_ArtistCredit(0),
	m_ReleaseGroup(0),
	m_LabelInfoList(0),
	m_MediumList(0),
	m_RelationList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Release node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			else if ("status"==NodeName)
			{
				m_Status=NodeValue;
			}
			else if ("quality"==NodeName)
			{
				m_Quality=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("packaging"==NodeName)
			{
				m_Packaging=NodeValue;
			}
			else if ("text-representation"==NodeName)
			{
				m_TextRepresentation=new CTextRepresentation(ChildNode);
			}
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=new CArtistCredit(ChildNode);
			}
			else if ("release-group"==NodeName)
			{
				m_ReleaseGroup=new CReleaseGroup(ChildNode);
			}
			
			else if ("date"==NodeName)
			{
				m_Date=NodeValue;
			}
			else if ("country"==NodeName)
			{
				m_Country=NodeValue;
			}
			else if ("barcode"==NodeName)
			{
				m_Barcode=NodeValue;
			}
			else if ("asin"==NodeName)
			{
				m_ASIN=NodeValue;
			}
			else if ("label-info-list"==NodeName)
			{
				m_LabelInfoList=new CGenericList<CLabelInfo>(ChildNode,"label-info");
			}
			else if ("medium-list"==NodeName)
			{
				m_MediumList=new CGenericList<CMedium>(ChildNode,"medium");
			}
			else if ("relation-list"==NodeName)
			{
				m_RelationList=new CGenericList<CRelation>(ChildNode,"relation");
			}
			else
			{
				std::cerr << "Unrecognised release node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CRelease::CRelease(const CRelease& Other)
:	m_TextRepresentation(0),
	m_ArtistCredit(0),
	m_ReleaseGroup(0),
	m_LabelInfoList(0),
	m_MediumList(0),
	m_RelationList(0)
{
	*this=Other;
}

MusicBrainzADH::CRelease& MusicBrainzADH::CRelease::operator =(const CRelease& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_ID=Other.m_ID;
		m_Title=Other.m_Title;
		m_Status=Other.m_Status;
		m_Quality=Other.m_Quality;
		m_Disambiguation=Other.m_Disambiguation;
		m_Packaging=Other.m_Packaging;
		
		if (Other.m_TextRepresentation)
			m_TextRepresentation=new CTextRepresentation(*Other.m_TextRepresentation);
		
		if (Other.m_ArtistCredit)
			m_ArtistCredit=new CArtistCredit(*Other.m_ArtistCredit);
		
		if (Other.m_ReleaseGroup)
			m_ReleaseGroup=new CReleaseGroup(*Other.m_ReleaseGroup);

		m_Date=Other.m_Date;
		m_Country=Other.m_Country;
		m_Barcode=Other.m_Barcode;
		m_ASIN=Other.m_ASIN;
		
		if (Other.m_LabelInfoList)
			m_LabelInfoList=new CGenericList<CLabelInfo>(*Other.m_LabelInfoList);
		
		if (Other.m_MediumList)
			m_MediumList=new CGenericList<CMedium>(*Other.m_MediumList);
		
		if (Other.m_RelationList)
			m_RelationList=new CGenericList<CRelation>(*Other.m_RelationList);
	}
	
	return *this;
}

MusicBrainzADH::CRelease::~CRelease()
{
	Cleanup();
}

void MusicBrainzADH::CRelease::Cleanup()
{
	delete m_TextRepresentation;
	m_TextRepresentation=0;
	
	delete m_ArtistCredit;
	m_ArtistCredit=0;
	
	delete m_ReleaseGroup;
	m_ReleaseGroup=0;
	
	delete m_LabelInfoList;
	m_LabelInfoList=0;
	
	delete m_MediumList;
	m_MediumList=0;
	
	delete m_RelationList;
	m_RelationList=0;
}

std::string MusicBrainzADH::CRelease::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CRelease::Title() const
{
	return m_Title;
}

std::string MusicBrainzADH::CRelease::Status() const
{
	return m_Status;
}

std::string MusicBrainzADH::CRelease::Quality() const
{
	return m_Quality;
}

std::string MusicBrainzADH::CRelease::Disambiguation() const
{
	return m_Disambiguation;
}

std::string MusicBrainzADH::CRelease::Packaging() const
{
	return m_Packaging;
}

MusicBrainzADH::CTextRepresentation *MusicBrainzADH::CRelease::TextRepresentation() const
{
	return m_TextRepresentation;
}

MusicBrainzADH::CArtistCredit *MusicBrainzADH::CRelease::ArtistCredit() const
{
	return m_ArtistCredit;
}

MusicBrainzADH::CReleaseGroup *MusicBrainzADH::CRelease::ReleaseGroup() const
{
	return m_ReleaseGroup;
}

std::string MusicBrainzADH::CRelease::Date() const
{
	return m_Date;
}

std::string MusicBrainzADH::CRelease::Country() const
{
	return m_Country;
}

std::string MusicBrainzADH::CRelease::Barcode() const
{
	return m_Barcode;
}

std::string MusicBrainzADH::CRelease::ASIN() const
{
	return m_ASIN;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CLabelInfo> *MusicBrainzADH::CRelease::LabelInfoList() const
{
	return m_LabelInfoList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CMedium> *MusicBrainzADH::CRelease::MediumList() const
{
	return m_MediumList;
}

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelation> *MusicBrainzADH::CRelease::RelationList() const
{
	return m_RelationList;
}

std::vector<MusicBrainzADH::CMedium> MusicBrainzADH::CRelease::MediaMatchingDiscID(const std::string& DiscID) const
{
	std::vector<MusicBrainzADH::CMedium> Ret;
	
	std::vector<MusicBrainzADH::CMedium> Media=m_MediumList->Items();
	
	std::vector<MusicBrainzADH::CMedium>::const_iterator ThisMedium=Media.begin();
	while (ThisMedium!=Media.end())
	{
		MusicBrainzADH::CMedium Medium=(*ThisMedium);
		
		if (Medium.ContainsDiscID(DiscID))
			Ret.push_back(Medium);
			
		++ThisMedium;
	}
	
	return Ret;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRelease& Release)
{
	os << "Release:" << std::endl;
		
	os << "\tID:                  " << Release.ID() << std::endl;
	os << "\tTitle:               " << Release.Title() << std::endl;
	os << "\tStatus:              " << Release.Status() << std::endl;
	os << "\tQuality:             " << Release.Quality() << std::endl;
	os << "\tDisambiguation:      " << Release.Disambiguation() << std::endl;
	os << "\tPackaging:           " << Release.Packaging() << std::endl;
		
	if (Release.TextRepresentation())
		os << *Release.TextRepresentation();
		
	if (Release.ArtistCredit())
		os << *Release.ArtistCredit() << std::endl;
		
	if (Release.ReleaseGroup())
		os << *Release.ReleaseGroup() << std::endl;

	os << "\tDate:                " << Release.Date() << std::endl;
	os << "\tCountry:             " << Release.Country() << std::endl;
	os << "\tBarcode:             " << Release.Barcode() << std::endl;
	os << "\tASIN:                " << Release.ASIN() << std::endl;
		
	if (Release.LabelInfoList())
		os << *Release.LabelInfoList() << std::endl;
		
	if (Release.MediumList())
		os << *Release.MediumList() << std::endl;
		
	if (Release.RelationList())
		os << *Release.RelationList() << std::endl;

	return os;
}
