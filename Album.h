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

#ifndef _ALBUM_H
#define _ALBUM_H

#include <string>
#include <vector>

#include "Track.h"
#include "CoverArt.h"

class CAlbum
{
public:
	CAlbum();
	
	void AddTrack(const CTrack& Track);
	std::string Name() const;
	std::string Artist() const;
	std::string ArtistSort() const;
	std::string Date() const;
	std::string ASIN() const;
	std::vector<CTrack> Tracks() const;
	std::string ArtistID() const;
	std::string AlbumID() const;
	std::string Status() const;
	std::string Type() const;
	int DiskNumber() const;
	CCoverArt CoverArt() const;
		
	void SetDate(const std::string& Date);
	void SetName(const std::string& Name);
	void SetArtist(const std::string& Artist);
	void SetArtistSort(const std::string& ArtistSort);
	void SetASIN(const std::string& ASIN);
	void SetArtistID(const std::string& ArtistID);
	void SetAlbumID(const std::string& AlbumID);
	void SetDiskNumber(int DiskNumber);
	void SetStatus(const std::string& Status);
	void SetType(const std::string& Type);
	void SetCoverArt(const CCoverArt& CoverArt);
	
private:
	std::vector<CTrack> m_Tracks;
	std::string m_Name;
	std::string m_Artist;
	std::string m_ArtistSort;
	std::string m_Date;
	std::string m_ASIN;
	std::string m_ArtistID;
	std::string m_AlbumID;
	std::string m_Status;
	std::string m_Type;
	int m_DiskNumber;
	CCoverArt m_CoverArt;
};

#endif
