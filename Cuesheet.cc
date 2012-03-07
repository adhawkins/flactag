/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006 Andrew Hawkins
   
   This file is part of flactag.
   
   Flactag is free software; you can redistribute it and/or
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

#include "Cuesheet.h"

CCuesheet::CCuesheet()
:	m_Performer(""),
	m_Title(""),
	m_FileName("")
{
	Clear();
}

void CCuesheet::Clear()
{
	m_Leadout=(FLAC__uint64)-1;
	m_FirstTrack=255;
	m_LastTrack=255;
	
	m_Tracks.clear();
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

void CCuesheet::setPerformer(const std::string& Performer)
{
	m_Performer.assign(Performer);
}

void CCuesheet::setTitle(const std::string& Title)
{
	m_Title.assign(Title);
}

void CCuesheet::setFileName(const std::string& FileName)
{
	m_FileName.assign(FileName);
}

void CCuesheet::setTrackPerformer(int track, const std::string& Performer)
{
        m_Tracks[track].setPerformer(Performer);
}

void CCuesheet::setTrackTitle(int track, const std::string& Title)
{
        m_Tracks[track].setTitle(Title);
}

std::ostream& operator<<(std::ostream& os, const CCuesheet& cuesheet)
{
	FLAC__byte i;
	char Qsym = '"';
	os << "PERFORMER " << Qsym << cuesheet.m_Performer << Qsym << std::endl;
	os << "TITLE " << Qsym << cuesheet.m_Title << Qsym << std::endl;
	os << "FILE " << Qsym << cuesheet.m_FileName << Qsym << " FLAC" << std::endl;

	for(i = 1; i <= cuesheet.NumTracks(); i++)
	{
		os << cuesheet.Track(i);
	}
	return os;
}

