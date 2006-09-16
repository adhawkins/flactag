#ifndef _TAGS_WINDOW_H
#define _TAGS_WINDOW_H

#include "TagName.h"

class CTagsWindow
{
public:
	CTagsWindow(int Left, int Top, int Width, int Height);
	
	void Draw();
	bool NextLine();
	bool PreviousLine();
	void SetSelected(bool Selected);
	void SetModified(bool Modified);
	void SetTags(const tTagMap& Tags);
	
private:
	int m_Left;
	int m_Top;
	int m_Width;
	int m_Height;
	int m_TopVisible;
	int m_CurrentLine;
	bool m_Selected;
	tTagMap m_Tags;
	bool m_Modified;
};

#endif
