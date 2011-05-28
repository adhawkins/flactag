#ifndef _MBADH_TRACK_LIST_H
#define _MBADH_TRACK_LIST_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Track.h"

namespace MusicBrainzADH
{
	class CTrackList
	{
	public:
		CTrackList(const XMLNode& Node=XMLNode::emptyNode());
		
		std::vector<CTrack> Tracks() const;
		
	private:
		std::vector<CTrack> m_Tracks;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CTrackList& TrackList);

#endif