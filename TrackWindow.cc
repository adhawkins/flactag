#include "TrackWindow.h"

#include <sstream>
#include <iomanip>

#include <slang.h>

CTrackWindow::CTrackWindow(int Left, int Top, int Width, int Height, const std::vector<CAlbum>& Albums)
:	m_Left(Left),
	m_Top(Top),
	m_Width(Width),
	m_Height(Height),
	m_Albums(Albums),
	m_TopVisible(0),
	m_CurrentLine(0),
	m_Selected(false),
	m_CurrentAlbum(-1)
{
}

void CTrackWindow::SetCurrentAlbum(int Album)
{
	if (Album<m_Albums.size())
	{
		m_CurrentAlbum=Album;
		m_CurrentLine=0;
		m_TopVisible=0;
	}
}

void CTrackWindow::Draw()
{
	if (m_Selected)
		SLsmg_reverse_video();
	else
		SLsmg_normal_video();

	SLsmg_draw_box(m_Top,m_Left,m_Height,m_Width);
	SLsmg_gotorc(m_Top,m_Left+2);
	SLsmg_write_string(" Tracks ");
	SLsmg_normal_video();

	if (-1!=m_CurrentAlbum)
	{
		std::vector<CTrack> Tracks=m_Albums[m_CurrentAlbum].Tracks();
			
		int MaxTrack=m_TopVisible+m_Height-2;
		if (MaxTrack>Tracks.size())
			MaxTrack=Tracks.size();
	
		SLsmg_fill_region(m_Top+1,m_Left+1,m_Height-2,m_Width-2,' ');
				
		for (int count=m_TopVisible;count<MaxTrack;count++)
		{
			SLsmg_gotorc(count+m_Top+1-m_TopVisible,m_Left+1);
			if (count==m_CurrentLine)
				SLsmg_reverse_video();
			else
				SLsmg_normal_video();
				
			std::stringstream os;
			os << std::setw(2) << std::setfill(' ') << count+1 << ": " << Tracks[count].Artist() << " - " << Tracks[count].Name();
			SLsmg_write_nstring((char *)os.str().c_str(),m_Width-2);
		}
	}
}

bool CTrackWindow::NextLine()
{
	bool RetVal=false;
	
	std::vector<CTrack> Tracks=m_Albums[m_CurrentAlbum].Tracks();
		
	if (m_CurrentLine<Tracks.size()-1)
	{
		m_CurrentLine++;
		
		if (m_CurrentLine>=m_TopVisible+m_Height-2)
			m_TopVisible++;
			
		RetVal=true;
	}
	
	return RetVal;
}

bool CTrackWindow::PreviousLine()
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

void CTrackWindow::SetSelected(bool Selected)
{
	m_Selected=Selected;
}

