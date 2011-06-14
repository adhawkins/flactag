#ifndef _MBADH_TRACK_H
#define _MBADH_TRACK_H

#include <string>
#include <iostream>

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CRecording;

	class CTrack
	{
	public:
		CTrack(const XMLNode& Node=XMLNode::emptyNode());
		CTrack(const CTrack& Other);
		CTrack& operator =(const CTrack& Other);
		~CTrack();

		int Position() const;
		std::string Title() const;
		CRecording *Recording() const;

	private:
		void Cleanup();

		int m_Position;
		std::string m_Title;
		CRecording *m_Recording;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTrack& Track);

#endif
