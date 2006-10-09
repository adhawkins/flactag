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

#include "ScrollableWindow.h"

#include <slang.h>

CScrollableWindow::CScrollableWindow(const std::string& Title)
:	m_Left(0),
	m_Top(0),
	m_Width(SLtt_Screen_Rows),
	m_Height(SLtt_Screen_Cols),
	m_Title(Title),
	m_TopVisible(0),
	m_CurrentLine(0),
	m_Selected(false)
{
}

CScrollableWindow::~CScrollableWindow()
{
}

void CScrollableWindow::SetDimensions(int Left, int Top, int Width, int Height)
{
	m_Left=Left;
	m_Top=Top;
	m_Width=Width;
	m_Height=Height;
}

void CScrollableWindow::SetCurrentLine(int Line)
{
	m_CurrentLine=Line;
}

void CScrollableWindow::SetTopVisible(int Line)
{
	m_TopVisible=Line;
}

void CScrollableWindow::Draw()
{
	if (m_Selected)
		SLsmg_reverse_video();
	else
		SLsmg_normal_video();

	SLsmg_draw_box(m_Top,m_Left,m_Height,m_Width);
	SLsmg_gotorc(m_Top,m_Left+2);
	SLsmg_printf(" %s ",m_Title.c_str());
	SLsmg_normal_video();

	int MaxLine=m_TopVisible+m_Height-2;
	if (MaxLine>NumLines())
		MaxLine=NumLines();

	SLsmg_fill_region(m_Top+1,m_Left+1,m_Height-2,m_Width-2,' ');
			
	for (int count=m_TopVisible;count<MaxLine;count++)
	{
		SLsmg_gotorc(count+m_Top+1-m_TopVisible,m_Left+1);
		if (count==m_CurrentLine)
			SLsmg_reverse_video();
		else
			SLsmg_normal_video();
			
		SLsmg_write_nstring((char *)GetLine(count).c_str(),m_Width-2);
	}
}

bool CScrollableWindow::NextLine()
{
	bool RetVal=false;
	
	if (m_CurrentLine<NumLines()-1)
	{
		m_CurrentLine++;
		
		if (m_CurrentLine>=m_TopVisible+m_Height-2)
			m_TopVisible++;
			
		RetVal=true;
	}
	
	return RetVal;
}

bool CScrollableWindow::PreviousLine()
{
	bool RetVal=false;
	
	if (m_CurrentLine!=0)
	{
		m_CurrentLine--;

		if (m_CurrentLine<m_TopVisible)
			m_TopVisible--;
			
		RetVal=true;
	}
	
	return RetVal;
}

void CScrollableWindow::SetSelected(bool Selected)
{
	m_Selected=Selected;
}

int CScrollableWindow::CurrentLine() const
{
	return m_CurrentLine;
}

void CScrollableWindow::SetTitle(const std::string& Title)
{
	m_Title=Title;
}
