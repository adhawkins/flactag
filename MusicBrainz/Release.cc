//http://www.musicbrainz.org/ws/2/release/2bd8551b-7910-3647-a833-38b616257ed5?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits
//http://www.musicbrainz.org/ws/2/release/ae8c2094-f3a8-45f8-8c1b-09d069425526?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits
//http://www.musicbrainz.org/ws/2/release/8fd13191-2d9a-4670-b789-0c99a06278e0?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits

#include "Release.h"

#include <string.h>

#include "xmlParser/xmlParser.h"

MusicBrainzADH::CRelease::CRelease(const XMLNode& Node)
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
			else if ("text-representation"==NodeName)
			{
				m_TextRepresentation=CTextRepresentation(ChildNode);
			}
			else if ("date"==NodeName)
			{
				m_Date=NodeValue;
			}
			else if ("country"==NodeName)
			{
				m_Country=NodeValue;
			}
			else if ("asin"==NodeName)
			{
				m_ASIN=NodeValue;
			}
			else if ("barcode"==NodeName)
			{
				m_Barcode=NodeValue;
			}
			else if ("relation-list"==NodeName)
			{
				m_RelationList=CRelationList(ChildNode);
			}
			else if ("label-info-list"==NodeName)
			{
				m_LabelInfoList=CLabelInfoList(ChildNode);
			}
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=CArtistCredit(ChildNode);
			}
			else if ("release-group"==NodeName)
			{
				m_ReleaseGroup=CReleaseGroup(ChildNode);
			}
			else if ("medium-list"==NodeName)
			{
				m_MediumList=CMediumList(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised release node: '" << NodeName << "'" << std::endl;
			}
		}
	}
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

MusicBrainzADH::CTextRepresentation MusicBrainzADH::CRelease::TextRepresentation() const
{
	return m_TextRepresentation;
}

std::string MusicBrainzADH::CRelease::Date() const
{
	return m_Date;
}

std::string MusicBrainzADH::CRelease::Country() const
{
	return m_Country;
}

std::string MusicBrainzADH::CRelease::ASIN() const
{
	return m_ASIN;
}

std::string MusicBrainzADH::CRelease::Barcode() const
{
	return m_Barcode;
}

MusicBrainzADH::CRelationList MusicBrainzADH::CRelease::RelationList() const
{
	return m_RelationList;
}

MusicBrainzADH::CLabelInfoList MusicBrainzADH::CRelease::LabelInfoList() const
{
	return m_LabelInfoList;
}

MusicBrainzADH::CArtistCredit MusicBrainzADH::CRelease::ArtistCredit() const
{
	return m_ArtistCredit;
}

MusicBrainzADH::CReleaseGroup MusicBrainzADH::CRelease::ReleaseGroup() const
{
	return m_ReleaseGroup;
}

MusicBrainzADH::CMediumList MusicBrainzADH::CRelease::MediumList() const
{
	return m_MediumList;
}

std::vector<MusicBrainzADH::CMedium> MusicBrainzADH::CRelease::MediaMatchingDiscID(const std::string& DiscID) const
{
	std::vector<MusicBrainzADH::CMedium> Ret;
	
	std::vector<MusicBrainzADH::CMedium> Media=m_MediumList.Media();
	
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
	os << Release.TextRepresentation();
	os << "\tDate:                " << Release.Date() << std::endl;
	os << "\tCountry:             " << Release.Country() << std::endl;
	os << "\tASIN:                " << Release.ASIN() << std::endl;
	os << "\tBarcode:             " << Release.Barcode() << std::endl;
	os << Release.RelationList() << std::endl;
	os << Release.LabelInfoList() << std::endl;
	os << Release.ArtistCredit() << std::endl;
	os << Release.ReleaseGroup() << std::endl;
	os << Release.MediumList() << std::endl;

	return os;
}
