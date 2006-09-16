#ifndef _CUESHEET_H
#define _CUESHEET_H

#include <map>

#include "CuesheetTrack.h"

class CCuesheet
{
public:
	CCuesheet();
	
	void AddTrack(const CCuesheetTrack& Track);
	FLAC__byte NumTracks() const;
	CCuesheetTrack Track(FLAC__byte TrackNum) const;
	void SetLeadout(FLAC__uint64 Leadout);
	FLAC__uint64 Leadout() const;
	FLAC__byte FirstTrack() const;
	FLAC__byte LastTrack() const;
	
private:
	std::map<FLAC__byte,CCuesheetTrack> m_Tracks;
	FLAC__uint64 m_Leadout;
	FLAC__byte m_FirstTrack;
	FLAC__byte m_LastTrack;
};

#endif
