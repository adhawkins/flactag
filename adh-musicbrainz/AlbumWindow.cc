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

#include "AlbumWindow.h"

#include <sstream>
#include <iomanip>

#include "ErrorLog.h"

CAlbumWindow::CAlbumWindow(const std::vector<CAlbum>& Albums)
:	CScrollableWindow("Albums"),
	m_Albums(Albums)
{
}

int CAlbumWindow::GetCurrentAlbum() const
{
	return CurrentLine();
}

std::string CAlbumWindow::GetLine(int Line) const
{			
	std::stringstream os;
	os << std::setw(2) << std::setfill(' ') << Line+1 << ": " << m_Albums[Line].Artist().DisplayValue() << " - " << m_Albums[Line].Name().DisplayValue();
	if (-1!=m_Albums[Line].DiskNumber())
		os << " (disc " << m_Albums[Line].DiskNumber() << ")";

	return os.str();			
}

int CAlbumWindow::NumLines() const
{
	return m_Albums.size();
}
