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

#include "CoverArtFetch.h"

#include "config.h"

#include "ErrorLog.h"

#include "coverart/CoverArt.h"
#include "coverart/HTTPFetch.h"

#include "musicbrainz5/HTTPFetch.h"

CCoverArtFetch::CCoverArtFetch(const std::string &ReleaseID, const std::string &ASIN)
{
	Fetch(ReleaseID, ASIN);
}

CCoverArt CCoverArtFetch::CoverArt() const
{
	return m_CoverArt;
}

void CCoverArtFetch::Fetch(const std::string &ReleaseID, const std::string &ASIN)
{
	try
	{
		CoverArtArchive::CCoverArt CoverArt("flactag/v" VERSION);
		m_CoverArt = CCoverArt(CoverArt.FetchFront(ReleaseID));
	}

	catch (CoverArtArchive::CExceptionBase e)
	{
		std::vector<unsigned char> Data;

		std::string URL = "/images/P/" + ASIN + ".02.LZZZZZZZ.jpg";

		MusicBrainz5::CHTTPFetch Fetch("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.182 Safari/537.36", "images.amazon.com");

		int Bytes = Fetch.Fetch(URL);
		if (Bytes < 1000)
		{
			URL = "/images/P/" + ASIN + ".02.MZZZZZZZ.jpg";
			Bytes = Fetch.Fetch(URL);
		}

		if (Bytes > 0)
		{
			if (Bytes < 1000)
				CErrorLog::Log("Album art downloaded was less than 1000 bytes, ignoring");
			else
				m_CoverArt = CCoverArt(Fetch.Data());
		}
		else
			CErrorLog::Log(std::string("Error downloading art: ") + Fetch.ErrorMessage());
	}
}
