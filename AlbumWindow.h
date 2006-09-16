#ifndef _ALBUMWINDOW_H
#define _ALBUMWINDOW_H

#include "Album.h"

class CAlbumWindow
{
public:
	CAlbumWindow(int Left, int Top, int Width, int Height, const std::vector<CAlbum>& Albums);
	
	void Draw();
	bool NextLine();
	bool PreviousLine();
	int GetCurrentAlbum() const;
	void SetSelected(bool Selected);
	
private:
	int m_Left;
	int m_Top;
	int m_Width;
	int m_Height;
	int m_TopVisible;
	int m_CurrentLine;
	bool m_Selected;
	std::vector<CAlbum> m_Albums;
};

#endif
