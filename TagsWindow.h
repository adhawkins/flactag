#ifndef _TAGS_WINDOW_H
#define _TAGS_WINDOW_H

#include "TagName.h"
#include "ScrollableWindow.h"

class CTagsWindow: public CScrollableWindow
{
public:
	CTagsWindow(int Left, int Top, int Width, int Height);
	
	void SetTags(const tTagMap& Tags);
	void SetModified(bool Modified);
		
	virtual int NumLines() const;
	virtual std::string GetLine(int Line) const;
		
private:
	tTagMap m_Tags;
	bool m_Modified;
};

#endif
