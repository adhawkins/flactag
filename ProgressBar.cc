#include "ProgressBar.h"

#include <slang.h>

#include <cmath>
#include <sstream>

#ifdef NO_SLANG
#include <iostream>
#endif

std::mutex CProgressBar::m_DisplayMutex;

CProgressBar::CProgressBar(const std::string &Title)
		: m_Title(Title)
{
}

void CProgressBar::SetIndex(int Index)
{
	m_Index = Index;
}

void CProgressBar::SetTitle(const std::string &Title)
{
	m_Title = Title;
}

void CProgressBar::SetProgress(double Progress)
{
	m_Progress = Progress;
}

bool CProgressBar::Update(bool Force)
{
	bool Changed = m_Progress != m_LastProgress && m_Index != -1;
	if (Force || Changed)
	{
		m_LastProgress = m_Progress;

#ifdef NO_SLANG
		std::cout << "Index: " << m_Index << ": '" << m_Title << "' - " << m_Progress << "%" << std::endl;
#else
		int Width = SLtt_Screen_Cols - 8;
		int NumHashes = m_Progress * Width / 100;

		std::lock_guard<std::mutex> Lock(m_DisplayMutex);

		SLsmg_gotorc(m_Index * 2 + 0, 0);
		SLsmg_write_string(const_cast<char *>(m_Title.c_str()));

		SLsmg_gotorc(m_Index * 2 + 1, 0);

		SLsmg_write_char('[');

		for (int count = 0; count < Width; count++)
		{
			if (count < NumHashes)
				SLsmg_write_char('#');
			else
				SLsmg_write_char('.');
		}

		SLsmg_write_char(']');

		SLsmg_gotorc(m_Index * 2 + 1, SLtt_Screen_Cols - 5);
		SLsmg_printf(const_cast<char *>("%3d%%"), m_Progress);
#endif
	}

	return Changed;
}

void CProgressBar::ClearIndex(int Index)
{
#ifdef NO_SLANG
	std::cout << __PRETTY_FUNCTION__ << " - " << Index << std::endl;
#else
	std::lock_guard<std::mutex> Lock(m_DisplayMutex);

	SLsmg_fill_region(Index * 2, 0, 2, SLtt_Screen_Cols, ' ');
#endif
}
