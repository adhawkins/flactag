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

#ifndef _CUESHEET_TRACK_H
#define _CUESHEET_TRACK_H

#include <iostream>
#include <string>

#include <FLAC++/metadata.h>

class CCuesheetTrack
{
public:
	CCuesheetTrack(FLAC__byte Number=255, FLAC__uint64 Offset=(FLAC__uint64)-1);

	FLAC__byte Number() const;
	FLAC__uint64 Offset() const;

        void setPerformer(const std::string& Performer);
        void setTitle(const std::string& Title);

        friend std::ostream& operator<<(std::ostream& os, const CCuesheetTrack& track);

private:
	FLAC__byte m_Number;
	FLAC__uint64 m_Offset;
	std::string m_Performer;
	std::string m_Title;
};

#endif
