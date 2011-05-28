#ifndef _MBADH_RELEASE_H
#define _MBADH_RELEASE_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "TextRepresentation.h"
#include "RelationList.h"
#include "LabelInfoList.h"
#include "ArtistCredit.h"
#include "ReleaseGroup.h"
#include "MediumList.h"

namespace MusicBrainzADH
{
	class CRelease
	{
	public:
		CRelease(const XMLNode& Node=XMLNode::emptyNode());
		
		std::string ID() const;
		std::string Title() const;
		std::string Status() const;
		std::string Quality() const;
		CTextRepresentation TextRepresentation() const;
		std::string Date() const;
		std::string Country() const;
		std::string ASIN() const;
		std::string Barcode() const;
		CRelationList RelationList() const;
		CLabelInfoList LabelInfoList() const;
		CArtistCredit ArtistCredit() const;
		CReleaseGroup ReleaseGroup() const;
		CMediumList MediumList() const;
		
		std::vector<CMedium> MediaMatchingDiscID(const std::string& DiscID) const;
			
	private:
		std::string m_ID;
		std::string m_Title;
		std::string m_Status;
		std::string m_Quality;
		CTextRepresentation m_TextRepresentation;
		std::string m_Date;
		std::string m_Country;
		std::string m_ASIN;
		std::string m_Barcode;
		CRelationList m_RelationList;
		CLabelInfoList m_LabelInfoList;
		CArtistCredit m_ArtistCredit;
		CReleaseGroup m_ReleaseGroup;
		CMediumList m_MediumList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRelease& Release);

#endif