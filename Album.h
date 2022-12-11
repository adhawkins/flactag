/* --------------------------------------------------------------------------

	 flactag -- A tagger for single album FLAC files with embedded CUE sheets
							using data retrieved from the MusicBrainz service

	 Copyright (C) 2006-2022 Andrew Hawkins

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

#ifndef _ALBUM_H
#define _ALBUM_H

#include <string>
#include <vector>

#include "Track.h"
#include "CoverArt.h"
#include "UTF8Tag.h"

class CAlbum
{
public:
	CAlbum();

	void AddTrack(const CTrack& Track);
	CUTF8Tag Name() const;
	CUTF8Tag Artist() const;
	CUTF8Tag ArtistSort() const;
	CUTF8Tag Date() const;
	CUTF8Tag ASIN() const;
	CUTF8Tag Barcode() const;
	CUTF8Tag Country() const;
	std::vector<CTrack> Tracks() const;
	CUTF8Tag ArtistID() const;
	CUTF8Tag AlbumID() const;
	CUTF8Tag Status() const;
	CUTF8Tag Type() const;
	int DiskNumber() const;
	CCoverArt CoverArt() const;

	void SetBarcode(const CUTF8Tag &Barcode);
	void SetCountry(const CUTF8Tag &Country);
	void SetDate(const CUTF8Tag & Date);
	void SetName(const CUTF8Tag& Name);
	void SetArtist(const CUTF8Tag & Artist);
	void SetArtistSort(const CUTF8Tag & ArtistSort);
	void SetASIN(const CUTF8Tag & ASIN);
	void SetArtistID(const CUTF8Tag & ArtistID);
	void SetAlbumID(const CUTF8Tag & AlbumID);
	void SetDiskNumber(int DiskNumber);
	void SetStatus(const CUTF8Tag & Status);
	void SetType(const CUTF8Tag & Type);
	void SetCoverArt(const CCoverArt& CoverArt);

private:
	std::vector<CTrack> m_Tracks;
	CUTF8Tag m_Name;
	CUTF8Tag m_Artist;
	CUTF8Tag m_ArtistSort;
	CUTF8Tag m_Barcode;
	CUTF8Tag m_Country;
	CUTF8Tag m_Date;
	CUTF8Tag m_ASIN;
	CUTF8Tag m_ArtistID;
	CUTF8Tag m_AlbumID;
	CUTF8Tag m_Status;
	CUTF8Tag m_Type;
	int m_DiskNumber;
	CCoverArt m_CoverArt;
};

#endif
