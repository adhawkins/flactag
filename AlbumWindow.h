/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006 Andrew Hawkins

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

#ifndef _ALBUMWINDOW_H
#define _ALBUMWINDOW_H

#include "Album.h"
#include "ScrollableWindow.h"

class CAlbumWindow: public CScrollableWindow
{
public:
	CAlbumWindow(const std::vector<CAlbum>& Albums);

	int GetCurrentAlbum() const;

	virtual int NumLines() const;
	virtual std::string GetLine(int Line) const;

private:
	std::vector<CAlbum> m_Albums;
};

#endif
