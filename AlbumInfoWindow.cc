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

#include "AlbumInfoWindow.h"

#include <sstream>
#include <iomanip>

CAlbumInfoWindow::CAlbumInfoWindow(const std::vector<CAlbum> &Albums)
		: CScrollableWindow("Album Info"),
			m_CurrentAlbum(-1),
			m_Albums(Albums)
{
}

void CAlbumInfoWindow::SetCurrentAlbum(std::vector<CAlbum>::size_type Album)
{
	if (Album<m_Albums.size())
	{
		m_CurrentAlbum=Album;
		SetCurrentLine(0);
		SetTopVisible(0);

		m_Lines.clear();

		auto Album = m_Albums[m_CurrentAlbum];

		AddInfo("Release ID", Album.AlbumID());
		AddInfo("Barcode", Album.Barcode());
		AddInfo("Country", Album.Country());
		AddInfo("Date", Album.Date());
		AddInfo("ASIN", Album.ASIN());

		if (!m_Lines.empty())
			m_Lines.push_back("");

		auto Tracks = Album.Tracks();
		for (decltype(Tracks)::size_type Track = 0; Track < Tracks.size(); Track++)
		{
			std::stringstream os;
			os << "  " << std::setw(2) << std::setfill(' ') << Track + 1 << ":" << Tracks[Track].Artist().DisplayValue() << " - " << Tracks[Track].Name().DisplayValue();
			m_Lines.push_back(os.str());
		}
	}
}

int CAlbumInfoWindow::NumLines() const
{
	int RetVal=0;

	if (-1!=m_CurrentAlbum)
		RetVal = m_Lines.size();

	return RetVal;
}

std::string CAlbumInfoWindow::GetLine(size_t Line) const
{
	std::string RetVal;

	if (-1 != m_CurrentAlbum && Line < m_Lines.size())
	{
		RetVal = m_Lines[Line];
	}

	return RetVal;
}

void CAlbumInfoWindow::AddInfo(const std::string &Title, const CUTF8Tag &Tag)
{
	if (!Tag.empty())
	{
		std::stringstream os;
		os << Title << ": " << Tag.DisplayValue();
		m_Lines.push_back(os.str());
	}
}