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

void CAlbum::SetName(const std::string& Name)
{
	m_Name=Name;
}

void CAlbum::SetArtist(const std::string& Artist)
{
	m_Artist=Artist;
}

void CAlbum::SetArtistSort(const std::string& ArtistSort)
{
	m_ArtistSort=ArtistSort;
}

void CAlbum::SetASIN(const std::string& ASIN)
{
	m_ASIN=ASIN;
}

void CAlbum::SetDate(const std::string& Date)
{
	m_Date=Date;
}
	
void CAlbum::SetDiskNumber(int DiskNumber)
{
	m_DiskNumber=DiskNumber;
}

std::string CAlbum::Name() const
{
	return m_Name;
}

std::string CAlbum::Artist() const
{
	return m_Artist;
}

std::string CAlbum::ArtistSort() const
{
	return m_ArtistSort;
}

std::string CAlbum::Date() const
{
	return m_Date;
}

std::vector<CTrack> CAlbum::Tracks() const
{
	return m_Tracks;
}

std::string CAlbum::ASIN() const
{
	return m_ASIN;
}

int CAlbum::DiskNumber() const
{
	return m_DiskNumber;
}

std::string CAlbum::ArtistID() const
{
	return m_ArtistID;
}

std::string CAlbum::AlbumID() const
{
	return m_AlbumID;
}

std::string CAlbum::Status() const
{
	return m_Status;
}

std::string CAlbum::Type() const
{
	return m_Type;
}

void CAlbum::SetArtistID(const std::string& ArtistID)
{
	m_ArtistID=ArtistID;
}

void CAlbum::SetAlbumID(const std::string& AlbumID)
{
	m_AlbumID=AlbumID;
}

void CAlbum::SetStatus(const std::string& Status)
{
	m_Status=Status;
}

void CAlbum::SetType(const std::string& Type)
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

