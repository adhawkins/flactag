#ifndef _TRACK_WINDOW_H
#define _TRACK_WINDOW_H

#include <vector>

#include "Album.h"

class CTrackWindow
{
public:
	CTrackWindow(int Left, int Top, int Width, int Height, const std::vector<CAlbum>& Albums);
	
	void SetCurrentAlbum(std::vector<CAlbum>::size_type Album);
	void Draw();
	bool NextLine();
	bool PreviousLine();
	void SetSelected(bool Selected);
	
private:
	int m_Left;
	int m_Top;
	int m_Width;
	int m_Height;
	int m_TopVisible;
	int m_CurrentLine;
	bool m_Selected;
	int m_CurrentAlbum;
	std::vector<CAlbum> m_Albums;
};

#endif
