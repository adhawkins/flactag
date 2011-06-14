#ifndef _MBADH_RELEASE_H
#define _MBADH_RELEASE_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "GenericList.h"

namespace MusicBrainz4
{
	class CTextRepresentation;
	class CArtistCredit;
	class CReleaseGroup;
	class CLabelInfo;
	class CMedium;
	class CRelation;

	class CRelease
	{
	public:
		CRelease(const XMLNode& Node=XMLNode::emptyNode());
		CRelease(const CRelease& Other);
		CRelease& operator =(const CRelease& Other);
		~CRelease();

		std::string ID() const;
		std::string Title() const;
		std::string Status() const;
		std::string Quality() const;
		std::string Disambiguation() const;
		std::string Packaging() const;
		CTextRepresentation *TextRepresentation() const;
		CArtistCredit *ArtistCredit() const;
		CReleaseGroup *ReleaseGroup() const;
		std::string Date() const;
		std::string Country() const;
		std::string Barcode() const;
		std::string ASIN() const;
		CGenericList<CLabelInfo> *LabelInfoList() const;
		CGenericList<CMedium> *MediumList() const;
		CGenericList<CRelation> *RelationList() const;

		std::vector<CMedium> MediaMatchingDiscID(const std::string& DiscID) const;

	private:
		void Cleanup();

		std::string m_ID;
		std::string m_Title;
		std::string m_Status;
		std::string m_Quality;
		std::string m_Disambiguation;
		std::string m_Packaging;
		CTextRepresentation *m_TextRepresentation;
		CArtistCredit *m_ArtistCredit;
		CReleaseGroup *m_ReleaseGroup;
		std::string m_Date;
		std::string m_Country;
		std::string m_Barcode;
		std::string m_ASIN;
		CGenericList<CLabelInfo> *m_LabelInfoList;
		CGenericList<CMedium> *m_MediumList;
		CGenericList<CRelation> *m_RelationList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRelease& Release);

#endif