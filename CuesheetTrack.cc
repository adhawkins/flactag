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

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "CuesheetTrack.h"

CCuesheetTrack::CCuesheetTrack(FLAC__byte Number, FLAC__uint64 Offset)
:	m_Number(Number),
	m_Offset(Offset),
	m_Performer(""),
	m_Title("")
{
}

FLAC__byte CCuesheetTrack::Number() const
{
	return m_Number;
}

FLAC__uint64 CCuesheetTrack::Offset() const
{
	return m_Offset;
}

void CCuesheetTrack::setPerformer(const std::string& Performer)
{
        m_Performer.assign(Performer);
}

void CCuesheetTrack::setTitle(const std::string& Title)
{
        m_Title.assign(Title);
}

std::string doubleDigit(int num)
{
	std::stringstream os;
	os << std::right;
	os.fill('0');
	os << std::setw(2) << num;
	return os.str();
}

std::string CuesheetTrackIndex(FLAC__uint64 _offset)
{
	char sep = ':';
	std::stringstream os;
	int frames = _offset % 75;
	int _secs = ((_offset - frames) / 75) - 2;
	int secs = _secs % 60;
	int mins = (_secs - secs) / 60;
	os << doubleDigit(mins) << sep << doubleDigit(secs)
           << sep << doubleDigit(frames);
	return os.str();
}

std::ostream& operator<<(std::ostream& os, const CCuesheetTrack& track)
{
        char Qsym = '"';
	os << "  TRACK " << doubleDigit(track.Number()) << " AUDIO" << std::endl;
	os << "    INDEX 01 " << CuesheetTrackIndex(track.Offset()) << std::endl;
        os << "    PERFORMER " << Qsym << track.m_Performer << Qsym << std::endl;
        os << "    TITLE " << Qsym << track.m_Title << Qsym << std::endl;
        return os;
}

