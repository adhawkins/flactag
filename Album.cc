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

#include "Album.h"

CAlbum::CAlbum()
:	m_DiskNumber(-1)
{
}

void CAlbum::AddTrack(const CTrack& Track)
{
	m_Tracks.push_back(Track);
}

void CAlbum::SetName(const CUTF8Tag& Name)
{
	m_Name=Name;
}

void CAlbum::SetArtist(const CUTF8Tag& Artist)
{
	m_Artist=Artist;
}

void CAlbum::SetArtistSort(const CUTF8Tag& ArtistSort)
{
	m_ArtistSort=ArtistSort;
}

void CAlbum::SetASIN(const CUTF8Tag& ASIN)
{
	m_ASIN=ASIN;
}

void CAlbum::SetDate(const CUTF8Tag& Date)
{
	m_Date=Date;
}
	
void CAlbum::SetDiskNumber(int DiskNumber)
{
	m_DiskNumber=DiskNumber;
}

CUTF8Tag CAlbum::Name() const
{
	return m_Name;
}

CUTF8Tag CAlbum::Artist() const
{
	return m_Artist;
}

CUTF8Tag CAlbum::ArtistSort() const
{
	return m_ArtistSort;
}

CUTF8Tag CAlbum::Date() const
{
	return m_Date;
}

std::vector<CTrack> CAlbum::Tracks() const
{
	return m_Tracks;
}

CUTF8Tag CAlbum::ASIN() const
{
	return m_ASIN;
}

int CAlbum::DiskNumber() const
{
	return m_DiskNumber;
}

CUTF8Tag CAlbum::ArtistID() const
{
	return m_ArtistID;
}

CUTF8Tag CAlbum::AlbumID() const
{
	return m_AlbumID;
}

CUTF8Tag CAlbum::Status() const
{
	return m_Status;
}

CUTF8Tag CAlbum::Type() const
{
	return m_Type;
}

void CAlbum::SetArtistID(const CUTF8Tag& ArtistID)
{
	m_ArtistID=ArtistID;
}

void CAlbum::SetAlbumID(const CUTF8Tag& AlbumID)
{
	m_AlbumID=AlbumID;
}

void CAlbum::SetStatus(const CUTF8Tag& Status)
{
	m_Status=Status;
}

void CAlbum::SetType(const CUTF8Tag& Type)
{
	m_Type=Type;
}

void CAlbum::SetCoverArt(const CCoverArt& CoverArt)
{
	m_CoverArt=CoverArt;
}

CCoverArt CAlbum::CoverArt() const
{
	return m_CoverArt;
}

