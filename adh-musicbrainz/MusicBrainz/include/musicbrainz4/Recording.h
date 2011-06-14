#ifndef _MUSICBRAINZ4_RECORDING_H
#define _MUSICBRAINZ4_RECORDING_H

#include <string>
#include <iostream>

#include "GenericList.h"

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CArtistCredit;
	class CRelease;
	class CPUID;
	class CISRC;
	class CRelation;
	class CTag;
	class CUserTag;
	class CRating;
	class CUserRating;

	class CRecording
	{
	public:
		CRecording(const XMLNode& Node=XMLNode::emptyNode());
		CRecording(const CRecording& Other);
		CRecording& operator =(const CRecording& Other);
		~CRecording();

		std::string ID() const;
		std::string Title() const;
		std::string Length() const;
		std::string Disambiguation() const;
		CArtistCredit *ArtistCredit() const;
		CGenericList<CRelease> *ReleaseList() const;
		CGenericList<CPUID> *PUIDList() const;
		CGenericList<CISRC> *ISRCList() const;
		CGenericList<CRelation> *RelationList() const;
		CGenericList<CTag> *TagList() const;
		CGenericList<CUserTag> *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;

	private:
		void Cleanup();

		std::string m_ID;
		std::string m_Title;
		std::string m_Length;
		std::string m_Disambiguation;
		CArtistCredit *m_ArtistCredit;
		CGenericList<CRelease> *m_ReleaseList;
		CGenericList<CPUID> *m_PUIDList;
		CGenericList<CISRC> *m_ISRCList;
		CGenericList<CRelation> *m_RelationList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRecording& Recording);

#endif
