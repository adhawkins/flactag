#include "TagsWindow.h"

#include <sstream>
#include <iomanip>

CTagsWindow::CTagsWindow(int Left, int Top, int Width, int Height)
:	CScrollableWindow(Left,Top,Width,Height,"Tags"),
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

std::string CTagsWindow::GetLine(int Line) const
{
	tTagMap::const_iterator ThisTag=m_Tags.begin();

	int count;				
	for (count=0;ThisTag!=m_Tags.end() && count<Line;count++)
		++ThisTag;
		
	CTagName Name=(*ThisTag).first;
	std::string Value=(*ThisTag).second;
	
	std::stringstream os;
	os << Name.String() << "=" << Value;
	
	return os.str();
}

int CTagsWindow::NumLines() const
{
	return m_Tags.size();
}

