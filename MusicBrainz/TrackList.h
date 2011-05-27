#ifndef _TRACK_LIST_H
#define _TRACK_LIST_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Track.h"

class CTrackList
{
public:
	CTrackList(const XMLNode& Node=XMLNode::emptyNode());
	
	std::vector<CTrack> Tracks() const;
	
private:
	std::vector<CTrack> m_Tracks;

	friend std::ostream& operator << (std::ostream& os, const CTrackList& TrackList);
};

#endif