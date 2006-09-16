#ifndef _CUESHEET_H
#define _CUESHEET_H

#include <map>

#include "CuesheetTrack.h"

class CCuesheet
{
public:
	CCuesheet();
	
	void AddTrack(const CCuesheetTrack& Track);
	int NumTracks() const;
	CCuesheetTrack Track(int TrackNum) const;
	void SetLeadout(int Leadout);
	int Leadout() const;
	int FirstTrack() const;
	int LastTrack() const;
	
private:
	std::map<int,CCuesheetTrack> m_Tracks;
	int m_Leadout;
	int m_FirstTrack;
	int m_LastTrack;
};

#endif
