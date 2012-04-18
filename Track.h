/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006 Andrew Hawkins

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

#ifndef _TRACK_H
#define _TRACK_H

#include "UTF8Tag.h"

#include <FLAC++/metadata.h>

class CTrack
{
public:
	CTrack();

	FLAC__byte Number() const;
	CUTF8Tag Name() const;
	CUTF8Tag Artist() const;
	CUTF8Tag ArtistSort() const;
	CUTF8Tag ArtistID() const;
	CUTF8Tag TrackID() const;

	void SetNumber(FLAC__byte Number);
	void SetName(const CUTF8Tag& Name);
	void SetArtist(const CUTF8Tag& Artist);
	void SetArtistSort(const CUTF8Tag& ArtistSort);
	void SetArtistID(const CUTF8Tag& ArtistID);
	void SetTrackID(const CUTF8Tag& TrackID);


private:
	FLAC__byte m_Number;
	CUTF8Tag m_Name;
	CUTF8Tag m_Artist;
	CUTF8Tag m_ArtistSort;
	CUTF8Tag m_ArtistID;
	CUTF8Tag m_TrackID;
};

#endif
