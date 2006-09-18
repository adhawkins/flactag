#ifndef _ALBUMWINDOW_H
#define _ALBUMWINDOW_H

#include "Album.h"
#include "ScrollableWindow.h"

class CAlbumWindow: public CScrollableWindow
{
public:
	CAlbumWindow(int Left, int Top, int Width, int Height, const std::vector<CAlbum>& Albums);
	
	int GetCurrentAlbum() const;
	
	virtual int NumLines() const;
	virtual std::string GetLine(int Line) const;
		
private:
	std::vector<CAlbum> m_Albums;
};

#endif
