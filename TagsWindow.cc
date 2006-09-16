#include "TagsWindow.h"

#include <sstream>
#include <iomanip>

#include <slang.h>

CTagsWindow::CTagsWindow(int Left, int Top, int Width, int Height)
:	m_Left(Left),
	m_Top(Top),
	m_Width(Width),
	m_Height(Height),
	m_TopVisible(0),
	m_CurrentLine(0),
	m_Selected(false),
	m_Modified(false)
{
}

void CTagsWindow::SetModified(bool Modified)
{
	m_Modified=Modified;
}

void CTagsWindow::Draw()
{
	if (m_Selected)
		SLsmg_reverse_video();
	else
		SLsmg_normal_video();

	SLsmg_draw_box(m_Top,m_Left,m_Height,m_Width);
	SLsmg_gotorc(m_Top,m_Left+2);
	SLsmg_write_string(" Tags");
	
	if (m_Modified)
		SLsmg_write_string(" *");
		
	SLsmg_write_string(" ");
		
	SLsmg_normal_video();
		
	int MaxTag=m_TopVisible+m_Height-2;
	if ((tTagMap::size_type)MaxTag>m_Tags.size())
		MaxTag=m_Tags.size();

	SLsmg_fill_region(m_Top+1,m_Left+1,m_Height-2,m_Width-2,' ');

	tTagMap::const_iterator ThisTag=m_Tags.begin();

	int count;				
	for (count=0;ThisTag!=m_Tags.end() && count<m_TopVisible;count++)
		++ThisTag;
		
	while (ThisTag!=m_Tags.end() && count<MaxTag)
	{
		CTagName Name=(*ThisTag).first;
		std::string Value=(*ThisTag).second;
		
		SLsmg_gotorc(count+m_Top+1-m_TopVisible,m_Left+1);
		if (count==m_CurrentLine)
			SLsmg_reverse_video();
		else
			SLsmg_normal_video();
			
		std::stringstream os;
		os << Name.String() << "=" << Value;
		SLsmg_write_nstring((char *)os.str().c_str(),m_Width-2);
		
		++count;
		++ThisTag;
	}
}

bool CTagsWindow::NextLine()
{
	bool RetVal=false;
	
	if ((tTagMap::size_type)m_CurrentLine<m_Tags.size()-1)
	{
		m_CurrentLine++;
		
		if (m_CurrentLine>=m_TopVisible+m_Height-2)
			m_TopVisible++;
			
		RetVal=true;
	}
	
	return RetVal;
}

bool CTagsWindow::PreviousLine()
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

void CTagsWindow::SetSelected(bool Selected)
{
	m_Selected=Selected;
}

void CTagsWindow::SetTags(const tTagMap& Tags)
{
	m_Tags=Tags;
}
