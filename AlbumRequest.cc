#include "AlbumRequest.h"

CAlbumRequest::CAlbumRequest(const std::string &Title, int ProgressStep)
		: CThreadBase(false),
			m_ProgressBar(Title),
			m_Title(Title),
			m_ProgressStep(ProgressStep)
{
}

void CAlbumRequest::StartThread()
{
	CThreadBase::StartThread();
}

void CAlbumRequest::SetIndex(int Index)
{
	m_ProgressBar.SetIndex(Index);
}

bool CAlbumRequest::NeedsUpdate()
{
	bool Ret = m_NeedsUpdate;

	m_NeedsUpdate = false;

	return Ret;
}

void CAlbumRequest::ThreadProc()
{
	while (!m_Complete)
	{
		m_CurrentProgress += m_ProgressStep;
		if (m_CurrentProgress > 100)
		{
			m_Complete = true;
		}
		else
		{
			m_ProgressBar.SetProgress(m_CurrentProgress);
			bool NeedsUpdate = m_ProgressBar.Update();
			if (NeedsUpdate)
			{
				m_NeedsUpdate = true;
			}
		}

		if (!m_Complete)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}

void CAlbumRequest::ForceUpdate()
{
	m_ProgressBar.Update(true);
}