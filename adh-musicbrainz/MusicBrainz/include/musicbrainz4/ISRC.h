#ifndef _MUSICBRAINZ4_ISRC_H
#define _MUSICBRAINZ4_ISRC_H

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/Recording.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CISRC
	{
	public:
		CISRC(const XMLNode& Node=XMLNode::emptyNode());
		CISRC(const CISRC& Other);
		CISRC& operator =(const CISRC& Other);
		~CISRC();

		std::string ID() const;
		CGenericList<CRecording> *RecordingList() const;

	private:
		void Cleanup();

		std::string m_ID;
		CGenericList<CRecording> *m_RecordingList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CISRC& ISRC);

#endif
