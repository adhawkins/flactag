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

#include "Track.h"

CTrack::CTrack()
:	m_Number(255)
{
}

std::string CTrack::Artist() const
{
	return m_Artist;
}

std::string CTrack::Name() const
{
	return m_Name;
}

FLAC__byte CTrack::Number() const
{
	return m_Number;
}

std::string CTrack::ArtistSort() const
{
	return m_ArtistSort;
}
	
std::string CTrack::ArtistID() const
{
	return m_ArtistID;
}

std::string CTrack::TrackID() const
{
	return m_TrackID;
}

void CTrack::SetNumber(FLAC__byte Number)
{
	m_Number=Number;
}

void CTrack::SetName(const std::string& Name)
{
	m_Name=Name;
}

void CTrack::SetArtist(const std::string& Artist)
{
	m_Artist=Artist;
}
void CTrack::SetArtistSort(const std::string& ArtistSort)
{
	m_ArtistSort=ArtistSort;
}

void CTrack::SetArtistID(const std::string& ArtistID)
{
	m_ArtistID=ArtistID;
}

void CTrack::SetTrackID(const std::string& TrackID)
{
	m_TrackID=TrackID;
}
