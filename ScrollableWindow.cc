#include "ScrollableWindow.h"

#include <slang.h>

#include "ErrorLog.h"

CScrollableWindow::CScrollableWindow(int Left, int Top, int Width, int Height, const std::string& Title)
:	m_Left(Left),
	m_Top(Top),
	m_Width(Width),
	m_Height(Height),
	m_Title(Title),
	m_TopVisible(0),
	m_CurrentLine(0),
	m_Selected(false)
{
}

CScrollableWindow::~CScrollableWindow()
{
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
	CErrorLog::Log("In CScrollableWindow::NextLine");
		
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
