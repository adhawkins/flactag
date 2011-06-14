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

#ifndef _MUSICBRAINZ_INFO_H
#define _MUSICBRAINZ_INFO_H

#include <vector>

#include "Album.h"
#include "Cuesheet.h"

#include "MusicBrainz/Release.h"
#include "MusicBrainz/Medium.h"
#include "MusicBrainz/Track.h"
#include "MusicBrainz/ArtistCredit.h"

class CMusicBrainzInfo
{
public:
	CMusicBrainzInfo(const std::string& Server, const CCuesheet& Cuesheet);

	bool LoadInfo(const std::string& FlacFile);
	std::vector<CAlbum> Albums() const;

private:
	std::string AlbumType(const std::string Type) const;
	std::string AlbumStatus(const std::string Status) const;
	void WaitRequest() const;
	CAlbum ParseAlbum(const MusicBrainz4::CRelease& Release, const MusicBrainz4::CMedium& Medium);
	CTrack ParseTrack(const MusicBrainz4::CTrack& MBTrack);
	void ParseArtist(const MusicBrainz4::CArtistCredit* ArtistCredit, std::string& ArtistID, std::string& ArtistName, std::string& ArtistSort);
	std::vector<unsigned char> GetCoverArt(const CUTF8Tag& ASIN);

	std::vector<CAlbum> m_Albums;
	std::string m_Server;
	CCuesheet m_Cuesheet;
};

#endif
