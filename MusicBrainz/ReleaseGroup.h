#ifndef _MBADH_RELEASE_GROUP_H
#define _MBADH_RELEASE_GROUP_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "GenericList.h"

namespace MusicBrainz4
{
	class CArtistCredit;
	class CRelease;
	class CRelation;
	class CTag;
	class CUserTag;
	class CRating;
	class CUserRating;

	class CReleaseGroup
	{
	public:
		CReleaseGroup(const XMLNode& Node=XMLNode::emptyNode());
		CReleaseGroup(const CReleaseGroup& Other);
		CReleaseGroup& operator =(const CReleaseGroup& Other);
		~CReleaseGroup();

		std::string ID() const;
		std::string Type() const;
		std::string Title() const;
		std::string Comment() const;
		CArtistCredit *ArtistCredit() const;
		CGenericList<CRelease> *ReleaseList() const;
		CGenericList<CRelation> *RelationList() const;
		CGenericList<CTag> *TagList() const;
		CGenericList<CUserTag> *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;

	private:
		void Cleanup();

		std::string m_ID;
		std::string m_Type;
		std::string m_Title;
		std::string m_Comment;
		CArtistCredit *m_ArtistCredit;
		CGenericList<CRelease> *m_ReleaseList;
		CGenericList<CRelation> *m_RelationList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CReleaseGroup& ReleaseGroup);

#endif
