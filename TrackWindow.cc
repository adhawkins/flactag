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

#include "TrackWindow.h"

#include <sstream>
#include <iomanip>

CTrackWindow::CTrackWindow(const std::vector<CAlbum>& Albums)
:	CScrollableWindow("Tracks"),
	m_CurrentAlbum(-1),
	m_Albums(Albums)
{
}

void CTrackWindow::SetCurrentAlbum(std::vector<CAlbum>::size_type Album)
{
	if (Album<m_Albums.size())
	{
		m_CurrentAlbum=Album;
		SetCurrentLine(0);
		SetTopVisible(0);
	}
}

int CTrackWindow::NumLines() const
{
	int RetVal=0;
	
	if (-1!=m_CurrentAlbum)
		RetVal=m_Albums[m_CurrentAlbum].Tracks().size();
		
	return RetVal;
}

std::string CTrackWindow::GetLine(int Line) const
{
	std::string RetVal;
		
	if (-1!=m_CurrentAlbum)
	{
		CAlbum Album=m_Albums[m_CurrentAlbum];
		std::vector<CTrack> Tracks=Album.Tracks();
		
		std::stringstream os;
		os << std::setw(2) << std::setfill(' ') << Line+1 << ":" << Tracks[Line].Artist() << " - " << Tracks[Line].Name();
		
		RetVal=os.str();
	}
	
	return RetVal;
}

	
