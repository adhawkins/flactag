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

#include "TagsWindow.h"

#include <sstream>
#include <iomanip>

CTagsWindow::CTagsWindow()
:	CScrollableWindow("Tags"),
	m_Modified(false)
{
}

void CTagsWindow::SetTags(const tTagMap& Tags)
{
	m_Tags=Tags;
}

void CTagsWindow::SetModified(bool Modified)
{
	m_Modified=Modified;
	std::stringstream os;
	os << "Tags";

	if (m_Modified)
		os << " *";

	SetTitle(os.str());
}

std::string CTagsWindow::GetLine(size_t Line) const
{
	tTagMap::const_iterator ThisTag=m_Tags.begin();

	for (size_t count = 0; ThisTag != m_Tags.end() && count < Line; count++)
		++ThisTag;

	CTagName Name=(*ThisTag).first;
	CUTF8Tag Value=(*ThisTag).second;

	std::stringstream os;
	os << Name.String() << "=" << Value.DisplayValue();

	return os.str();
}

int CTagsWindow::NumLines() const
{
	return m_Tags.size();
}

