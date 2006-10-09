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

#ifndef _SCROLLABLE_WINDOW_H
#define _SCROLLABLE_WINDOW_H

#include <string>

class CScrollableWindow
{
public:
	CScrollableWindow(const std::string& Title);
	virtual ~CScrollableWindow();
	
	void Draw();
	bool NextLine();
	bool PreviousLine();
	void SetSelected(bool Selected);
	void SetTitle(const std::string& Title);
	void SetCurrentLine(int Line);
	void SetTopVisible(int Line);
	void SetDimensions(int Left, int Top, int Width, int Height);

	int CurrentLine() const;
	
	virtual int NumLines() const=0;
	virtual std::string GetLine(int Line) const=0;
		
private:
	int m_Left;
	int m_Top;
	int m_Width;
	int m_Height;
	std::string m_Title;
	int m_TopVisible;
	int m_CurrentLine;
	bool m_Selected;
};

#endif
