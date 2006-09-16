#include "Cuesheet.h"

CCuesheet::CCuesheet()
:	m_Leadout((FLAC__uint64)-1),
	m_FirstTrack(255),
	m_LastTrack(255)
{
}

void CCuesheet::AddTrack(const CCuesheetTrack& Track)
{
	m_Tracks[Track.Number()]=Track;
	if (255==m_LastTrack || Track.Number()>m_LastTrack)
		m_LastTrack=Track.Number();

	if (255==m_FirstTrack || Track.Number()<m_FirstTrack)
		m_FirstTrack=Track.Number();
}

FLAC__byte CCuesheet::NumTracks() const
{
	return m_Tracks.size();
}

CCuesheetTrack CCuesheet::Track(FLAC__byte TrackNum) const
{
	CCuesheetTrack Ret;
	
	std::map<FLAC__byte,CCuesheetTrack>::const_iterator ThisTrack=m_Tracks.find(TrackNum);
	if (m_Tracks.end()!=ThisTrack)
		Ret=(*ThisTrack).second;
		
	return Ret;
}

void CCuesheet::SetLeadout(FLAC__uint64 Leadout)
{
	m_Leadout=Leadout;
}

FLAC__uint64 CCuesheet::Leadout() const
{
	return m_Leadout;
}

FLAC__byte CCuesheet::FirstTrack() const
{
	return m_FirstTrack;
}

FLAC__byte CCuesheet::LastTrack() const
{
	return m_LastTrack;
}
