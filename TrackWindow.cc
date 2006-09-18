#include "TrackWindow.h"

#include <sstream>
#include <iomanip>

CTrackWindow::CTrackWindow(int Left, int Top, int Width, int Height, const std::vector<CAlbum>& Albums)
:	CScrollableWindow(Left,Top,Width,Height,"Tracks"),
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

	
