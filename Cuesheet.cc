#include "Cuesheet.h"

CCuesheet::CCuesheet()
:	m_Leadout(-1),
	m_FirstTrack(-1),
	m_LastTrack(-1)
{
}

void CCuesheet::AddTrack(const CCuesheetTrack& Track)
{
	m_Tracks[Track.Number()]=Track;
	if (-1==m_LastTrack || Track.Number()>m_LastTrack)
		m_LastTrack=Track.Number();

	if (-1==m_FirstTrack || Track.Number()<m_FirstTrack)
		m_FirstTrack=Track.Number();
}

int CCuesheet::NumTracks() const
{
	return m_Tracks.size();
}

CCuesheetTrack CCuesheet::Track(int TrackNum) const
{
	CCuesheetTrack Ret;
	
	std::map<int,CCuesheetTrack>::const_iterator ThisTrack=m_Tracks.find(TrackNum);
	if (m_Tracks.end()!=ThisTrack)
		Ret=(*ThisTrack).second;
		
	return Ret;
}

void CCuesheet::SetLeadout(int Leadout)
{
	m_Leadout=Leadout;
}

int CCuesheet::Leadout() const
{
	return m_Leadout;
}

int CCuesheet::FirstTrack() const
{
	return m_FirstTrack;
}

int CCuesheet::LastTrack() const
{
	return m_LastTrack;
}
