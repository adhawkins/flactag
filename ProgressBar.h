#ifndef _PROGRESS_BAR_H
#define _PROGRESS_BAR_H

#include <mutex>
#include <string>
#include <vector>

// #define NO_SLANG

class CProgressBar
{
public:
	CProgressBar(const std::string &Title = "");

	void SetIndex(int Index);
	void SetTitle(const std::string &Title);
	void SetProgress(double Progress);
	bool Update(bool Force = false);
	int Index() const { return m_Index; }
	static void ClearIndex(int Index);

private:
	int m_Index = -1;
	std::string m_Title;
	int m_Progress = 0;
	int m_LastProgress = 0;

	static std::mutex m_DisplayMutex;
};

#endif
