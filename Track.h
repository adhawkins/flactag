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

#ifndef _TRACK_H
#define _TRACK_H

#include <string>

#include <FLAC++/metadata.h>

class CTrack
{
public:
	CTrack();

	FLAC__byte Number() const;
	std::string Name() const;
	std::string Artist() const;
	std::string ArtistSort() const;
	std::string ArtistID() const;
		
	void SetNumber(FLAC__byte Number);
	void SetName(const std::string& Name);
	void SetArtist(const std::string& Artist);
	void SetArtistSort(const std::string& ArtistSort);
	void SetArtistID(const std::string& ArtistID);
		
		
private:
	FLAC__byte m_Number;
	std::string m_Name;
	std::string m_Artist;
	std::string m_ArtistSort;
	std::string m_ArtistID;
};

#endif
