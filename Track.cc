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

#include "Track.h"

CTrack::CTrack()
:	m_Number(255)
{
}

CUTF8Tag CTrack::Artist() const
{
	return m_Artist;
}

CUTF8Tag CTrack::Name() const
{
	return m_Name;
}

FLAC__byte CTrack::Number() const
{
	return m_Number;
}

CUTF8Tag CTrack::ArtistSort() const
{
	return m_ArtistSort;
}

CUTF8Tag CTrack::ArtistID() const
{
	return m_ArtistID;
}

CUTF8Tag CTrack::TrackID() const
{
	return m_TrackID;
}

void CTrack::SetNumber(FLAC__byte Number)
{
	m_Number=Number;
}

void CTrack::SetName(const CUTF8Tag& Name)
{
	m_Name=Name;
}

void CTrack::SetArtist(const CUTF8Tag& Artist)
{
	m_Artist=Artist;
}
void CTrack::SetArtistSort(const CUTF8Tag& ArtistSort)
{
	m_ArtistSort=ArtistSort;
}

void CTrack::SetArtistID(const CUTF8Tag& ArtistID)
{
	m_ArtistID=ArtistID;
}

void CTrack::SetTrackID(const CUTF8Tag& TrackID)
{
	m_TrackID=TrackID;
}
