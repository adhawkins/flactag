/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_METADATA_H
#define _MUSICBRAINZ4_METADATA_H

#include <string>

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CArtist;
	class CRelease;
	class CReleaseGroup;
	class CRecording;
	class CLabel;
	class CWork;
	class CPUID;
	class CISRC;
	class CDisc;
	class CLabelInfo;
	class CRating;
	class CUserRating;
	class CCollection;
	class CArtist;
	class CRelease;
	class CReleaseGroup;
	class CRecording;
	class CLabel;
	class CWork;
	class CAnnotation;
	class CCDStub;
	class CFreeDBDisc;
	class CTag;
	class CUserTag;
	class CCollection;
	class CCDStub;

	class CMetadata
	{
	public:
		CMetadata(const XMLNode& Node=XMLNode::emptyNode());
		CMetadata(const CMetadata& Other);
		CMetadata& operator =(const CMetadata& Other);
		~CMetadata();

		std::string Generator() const;
		std::string Created() const;
		CArtist *Artist() const;
		CRelease *Release() const;
		CReleaseGroup *ReleaseGroup() const;
		CRecording *Recording() const;
		CLabel *Label() const;
		CWork *Work() const;
		CPUID *PUID() const;
		CISRC *ISRC() const;
		CDisc *Disc() const;
		CGenericList<CLabelInfo> *LabelInfoList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;
		CCollection *Collection() const;
		CGenericList<CArtist> *ArtistList() const;
		CGenericList<CRelease> *ReleaseList() const;
		CGenericList<CReleaseGroup> *ReleaseGroupList() const;
		CGenericList<CRecording> *RecordingList() const;
		CGenericList<CLabel> *LabelList() const;
		CGenericList<CWork> *WorkList() const;
		CGenericList<CISRC> *ISRCList() const;
		CGenericList<CAnnotation> *AnnotationList() const;
		CGenericList<CCDStub> *CDStubList() const;
		CGenericList<CFreeDBDisc> *FreeDBDiscList() const;
		CGenericList<CTag> *TagList() const;
		CGenericList<CUserTag> *UserTagList() const;
		CGenericList<CCollection> *CollectionList() const;
		CCDStub *CDStub() const;

	private:
		void Cleanup();

		std::string m_Generator;
		std::string m_Created;
		CArtist *m_Artist;
		CRelease *m_Release;
		CReleaseGroup *m_ReleaseGroup;
		CRecording *m_Recording;
		CLabel *m_Label;
		CWork *m_Work;
		CPUID *m_PUID;
		CISRC *m_ISRC;
		CDisc *m_Disc;
		CGenericList<CLabelInfo> *m_LabelInfoList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
		CCollection *m_Collection;
		CGenericList<CArtist> *m_ArtistList;
		CGenericList<CRelease> *m_ReleaseList;
		CGenericList<CReleaseGroup> *m_ReleaseGroupList;
		CGenericList<CRecording> *m_RecordingList;
		CGenericList<CLabel> *m_LabelList;
		CGenericList<CWork> *m_WorkList;
		CGenericList<CISRC> *m_ISRCList;
		CGenericList<CAnnotation> *m_AnnotationList;
		CGenericList<CCDStub> *m_CDStubList;
		CGenericList<CFreeDBDisc> *m_FreeDBDiscList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CGenericList<CCollection> *m_CollectionList;
		CCDStub *m_CDStub;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMetadata& Metadata);

#endif
