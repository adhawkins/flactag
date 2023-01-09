/* --------------------------------------------------------------------------

	 flactag -- A tagger for single album FLAC files with embedded CUE sheets
							using data retrieved from the MusicBrainz service

	 Copyright (C) 2006-2022 Andrew Hawkins
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

#ifndef _MUSICBRAINZ_INFO_H
#define _MUSICBRAINZ_INFO_H

#include <vector>

#include "Album.h"
#include "ConfigFile.h"
#include "Cuesheet.h"
#include "DiscIDWrapper.h"

#include "musicbrainz5/Release.h"
#include "musicbrainz5/Medium.h"
#include "musicbrainz5/Track.h"
#include "musicbrainz5/ArtistCredit.h"

class CMusicBrainzInfo
{
public:
	CMusicBrainzInfo(const CConfigFile &ConfigFile, const CCuesheet &Cuesheet, bool OverrideDiskID, const std::string &DiskID);

	bool LoadInfo(const std::string& FlacFile);
	std::vector<CAlbum> Albums() const;

private:
	std::string AlbumType(const std::string Type) const;
	std::string AlbumStatus(const std::string Status) const;
	CAlbum ParseAlbum(const MusicBrainz5::CRelease *Release, const MusicBrainz5::CMedium *Medium);
	CTrack ParseTrack(const MusicBrainz5::CTrack* MBTrack);
	void ParseArtist(const MusicBrainz5::CArtistCredit* ArtistCredit, std::string& ArtistID, std::string& ArtistName, std::string& ArtistSort);
	CCoverArt GetCoverArt(const CUTF8Tag &ReleaseID, const CUTF8Tag &ASIN);

	std::vector<CAlbum> m_Albums;
	CConfigFile m_ConfigFile;
	std::string m_Server;
	int m_Port;
	CCuesheet m_Cuesheet;
	CDiscIDWrapper m_DiscIDWrapper;
	std::string m_DiskID;
	bool m_OverrideDiskID;
};

#endif
