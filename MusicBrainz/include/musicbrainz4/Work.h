#ifndef _MUSICBRAINZ4_WORK_H
#define _MUSICBRAINZ4_WORK_H

#include <string>

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CArtistCredit;
	class CISWC;
	class CAlias;
	class CRelation;
	class CTag;
	class CUserTag;
	class CRating;
	class CUserRating;

	class CWork
	{
	public:
		CWork(const XMLNode& Node=XMLNode::emptyNode());
		CWork(const CWork& Other);
		CWork& operator =(const CWork& Other);
		~CWork();

		std::string ID() const;
		std::string Type() const;
		std::string Title() const;
		CArtistCredit *ArtistCredit() const;
		std::string ISWC() const;
		std::string Disambiguation() const;
		CGenericList<CAlias> *AliasList() const;
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
		CArtistCredit *m_ArtistCredit;
		std::string m_ISWC;
		std::string m_Disambiguation;
		CGenericList<CAlias> *m_AliasList;
		CGenericList<CRelation> *m_RelationList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CWork& Work);

#endif

