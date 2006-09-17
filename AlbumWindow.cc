#include "AlbumWindow.h"

#include <sstream>
#include <iomanip>

#include <slang.h>

CAlbumWindow::CAlbumWindow(int Left, int Top, int Width, int Height, const std::vector<CAlbum>& Albums)
:	m_Left(Left),
	m_Top(Top),
	m_Width(Width),
	m_Height(Height),
	m_TopVisible(0),
	m_CurrentLine(0),
	m_Selected(false),
	m_Albums(Albums)
{
}

void CAlbumWindow::Draw()
{
	if (m_Selected)
		SLsmg_reverse_video();
	else
		SLsmg_normal_video();

	SLsmg_draw_box(m_Top,m_Left,m_Height,m_Width);
	SLsmg_gotorc(m_Top,m_Left+2);
	SLsmg_write_string(" Albums ");
	SLsmg_normal_video();
	
	std::vector<CAlbum>::size_type MaxAlbum=m_TopVisible+m_Height-2;
	if (MaxAlbum>m_Albums.size())
		MaxAlbum=m_Albums.size();

	SLsmg_fill_region(m_Top+1,m_Left+1,m_Height-2,m_Width-2,' ');
			
	for (std::vector<CAlbum>::size_type count=m_TopVisible;count<MaxAlbum;count++)
	{
		SLsmg_gotorc(count+m_Top+1-m_TopVisible,m_Left+1);
		if (count==(std::vector<CAlbum>::size_type)m_CurrentLine)
			SLsmg_reverse_video();
		else
			SLsmg_normal_video();
			
		std::stringstream os;
		os << std::setw(2) << std::setfill(' ') << count+1 << ": " << m_Albums[count].Artist() << " - " << m_Albums[count].Name();
		if (-1!=m_Albums[count].DiskNumber())
			os << " (disc " << m_Albums[count].DiskNumber() << ")";
			
		SLsmg_write_nstring((char *)os.str().c_str(),m_Width-2);
	}
}

bool CAlbumWindow::NextLine()
{
	bool RetVal=false;
	
	if (std::vector<CAlbum>::size_type(m_CurrentLine)<m_Albums.size()-1)
	{
		m_CurrentLine++;
		
		if (m_CurrentLine>=m_TopVisible+m_Height-2)
			m_TopVisible++;
			
		RetVal=true;
	}
	
	return RetVal;
}

bool CAlbumWindow::PreviousLine()
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

int CAlbumWindow::GetCurrentAlbum() const
{
	return m_CurrentLine;
}

void CAlbumWindow::SetSelected(bool Selected)
{
	m_Selected=Selected;
}
