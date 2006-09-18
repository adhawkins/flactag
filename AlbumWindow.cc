#include "AlbumWindow.h"

#include <sstream>
#include <iomanip>

CAlbumWindow::CAlbumWindow(int Left, int Top, int Width, int Height, const std::vector<CAlbum>& Albums)
:	CScrollableWindow(Left,Top,Width,Height,"Albums"),
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
	os << std::setw(2) << std::setfill(' ') << Line+1 << ": " << m_Albums[Line].Artist() << " - " << m_Albums[Line].Name();
	if (-1!=m_Albums[Line].DiskNumber())
		os << " (disc " << m_Albums[Line].DiskNumber() << ")";

	return os.str();			
}

int CAlbumWindow::NumLines() const
{
	return m_Albums.size();
}
