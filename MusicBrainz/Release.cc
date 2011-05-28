//http://www.musicbrainz.org/ws/2/release/2bd8551b-7910-3647-a833-38b616257ed5?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits
//http://www.musicbrainz.org/ws/2/release/ae8c2094-f3a8-45f8-8c1b-09d069425526?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits
//http://www.musicbrainz.org/ws/2/release/8fd13191-2d9a-4670-b789-0c99a06278e0?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits

#include "Release.h"

#include <string.h>

#include "xmlParser/xmlParser.h"

CRelease::CRelease(const XMLNode& Node)
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

std::string CRelease::ID() const
{
	return m_ID;
}

std::string CRelease::Title() const
{
	return m_Title;
}

std::string CRelease::Status() const
{
	return m_Status;
}

std::string CRelease::Quality() const
{
	return m_Quality;
}

CTextRepresentation CRelease::TextRepresentation() const
{
	return m_TextRepresentation;
}

std::string CRelease::Date() const
{
	return m_Date;
}

std::string CRelease::Country() const
{
	return m_Country;
}

std::string CRelease::ASIN() const
{
	return m_ASIN;
}

std::string CRelease::Barcode() const
{
	return m_Barcode;
}

CLabelInfoList CRelease::LabelInfoList() const
{
	return m_LabelInfoList;
}

CArtistCredit CRelease::ArtistCredit() const
{
	return m_ArtistCredit;
}

CReleaseGroup CRelease::ReleaseGroup() const
{
	return m_ReleaseGroup;
}

CMediumList CRelease::MediumList() const
{
	return m_MediumList;
}

std::vector<CMedium> CRelease::MediaMatchingDiscID(const std::string& DiscID) const
{
	std::vector<CMedium> Ret;
	
	std::vector<CMedium> Media=m_MediumList.Media();
	
	std::vector<CMedium>::const_iterator ThisMedium=Media.begin();
	while (ThisMedium!=Media.end())
	{
		CMedium Medium=(*ThisMedium);
		
		std::cout << "Checking medium " << Medium.Position() << " for disc id '" << DiscID << "'" << std::endl;
			
		if (Medium.ContainsDiscID(DiscID))
			Ret.push_back(Medium);
			
		++ThisMedium;
	}
	
	return Ret;
}

std::ostream& operator << (std::ostream& os, const CRelease& Release)
{
	os << "Release:" << std::endl;
		
	os << "\tID:                  " << Release.m_ID << std::endl;
	os << "\tTitle:               " << Release.m_Title << std::endl;
	os << "\tStatus:              " << Release.m_Status << std::endl;
	os << "\tQuality:             " << Release.m_Quality << std::endl;
	os << Release.m_TextRepresentation;
	os << "\tDate:                " << Release.m_Date << std::endl;
	os << "\tCountry:             " << Release.m_Country << std::endl;
	os << "\tASIN:                " << Release.m_ASIN << std::endl;
	os << "\tBarcode:             " << Release.m_Barcode << std::endl;
	os << Release.m_RelationList << std::endl;
	os << Release.m_LabelInfoList << std::endl;
	os << Release.m_ArtistCredit << std::endl;
	os << Release.m_ReleaseGroup << std::endl;
	os << Release.m_MediumList << std::endl;

	return os;
}
