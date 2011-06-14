#ifndef _MUSICBRAINZ4_ARTIST_H
#define _MUSICBRAINZ4_ARTIST_H

#include <string>
#include <iostream>

#include "GenericList.h"

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CLifespan;
	class CAlias;
	class CRecording;
	class CRelease;
	class CReleaseGroup;
	class CLabel;
	class CWork;
	class CRelation;
	class CTag;
	class CUserTag;
	class CRating;
	class CUserRating;

	class CArtist
	{
	public:
		CArtist(const XMLNode& Node=XMLNode::emptyNode());
		CArtist(const CArtist& Other);
		CArtist& operator =(const CArtist& Other);
		~CArtist();

		std::string ID() const;
		std::string Type() const;
		std::string Name() const;
		std::string SortName() const;
		std::string Gender() const;
		std::string Country() const;
		std::string Disambiguation() const;
		CLifespan *Lifespan() const;
		CGenericList<CAlias> *AliasList() const;
		CGenericList<CRecording> *RecordingList() const;
		CGenericList<CRelease> *ReleaseList() const;
		CGenericList<CReleaseGroup> *ReleaseGroupList() const;
		CGenericList<CLabel> *LabelList() const;
		CGenericList<CWork> *WorkList() const;
		CGenericList<CRelation> *RelationList() const;
		CGenericList<CTag> *TagList() const;
		CGenericList<CUserTag> *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;

	private:
		void Cleanup();

		std::string m_ID;
		std::string m_Type;
		std::string m_Name;
		std::string m_SortName;
		std::string m_Gender;
		std::string m_Country;
		std::string m_Disambiguation;
		CLifespan *m_Lifespan;
		CGenericList<CAlias> *m_AliasList;
		CGenericList<CRecording> *m_RecordingList;
		CGenericList<CRelease> *m_ReleaseList;
		CGenericList<CReleaseGroup> *m_ReleaseGroupList;
		CGenericList<CLabel> *m_LabelList;
		CGenericList<CWork> *m_WorkList;
		CGenericList<CRelation> *m_RelationList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CArtist& Artist);

#endif
