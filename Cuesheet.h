/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2012 Andrew Hawkins
   Copyright (C) 2011-2012 Daniel Pocock

   This file is part of flactag.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
	 the Free Software Foundation, either version 3 of the License, or
	 (at your option) any later version.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _CUESHEET_H
#define _CUESHEET_H

#include <map>
#include <iostream>

#include "CuesheetTrack.h"

class CCuesheet
{
public:
	CCuesheet();

	void Clear();

	void AddTrack(const CCuesheetTrack& Track);
	FLAC__byte NumTracks() const;
	CCuesheetTrack Track(FLAC__byte TrackNum) const;
	void SetLeadout(FLAC__uint64 Leadout);
	FLAC__uint64 Leadout() const;
	FLAC__byte FirstTrack() const;
	FLAC__byte LastTrack() const;

	void setPerformer(const std::string& Performer);
	void setTitle(const std::string& Title);
	void setFileName(const std::string& FileName);

	void setTrackPerformer(int track, const std::string& Performer);
	void setTrackTitle(int track, const std::string& Title);

	friend std::ostream& operator<<(std::ostream& os, const CCuesheet& cuesheet);

private:
	std::map<FLAC__byte,CCuesheetTrack> m_Tracks;
	FLAC__uint64 m_Leadout;
	FLAC__byte m_FirstTrack;
	FLAC__byte m_LastTrack;
	std::string m_Performer;
	std::string m_Title;
	std::string m_FileName;
};

#endif
