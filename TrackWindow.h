#ifndef _TRACK_WINDOW_H
#define _TRACK_WINDOW_H

#include <vector>

#include "ScrollableWindow.h"
#include "Album.h"

class CTrackWindow: public CScrollableWindow
{
public:
	CTrackWindow(int Left, int Top, int Width, int Height, const std::vector<CAlbum>& Albums);
	
	void SetCurrentAlbum(std::vector<CAlbum>::size_type Album);
	
	virtual int NumLines() const;
	virtual std::string GetLine(int Line) const;
		
private:
	int m_CurrentAlbum;
	std::vector<CAlbum> m_Albums;
};

#endif
