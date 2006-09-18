#ifndef _SCROLLABLE_WINDOW_H
#define _SCROLLABLE_WINDOW_H

#include <string>

class CScrollableWindow
{
public:
	CScrollableWindow(int Left, int Top, int Width, int Height, const std::string& Title);
	virtual ~CScrollableWindow();
	
	void Draw();
	bool NextLine();
	bool PreviousLine();
	void SetSelected(bool Selected);
	void SetTitle(const std::string& Title);
	void SetCurrentLine(int Line);
	void SetTopVisible(int Line);

	int CurrentLine() const;
	
	virtual int NumLines() const=0;
	virtual std::string GetLine(int Line) const=0;
		
private:
	int m_Left;
	int m_Top;
	int m_Width;
	int m_Height;
	std::string m_Title;
	int m_TopVisible;
	int m_CurrentLine;
	bool m_Selected;
};

#endif
