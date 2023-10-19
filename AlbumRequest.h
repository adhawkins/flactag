#ifndef _ALBUM_REQUEST_H
#define _ALBUM_REQUEST_H

#include <string>

#include "ProgressBar.h"
#include "ThreadBase.h"

class CAlbumRequest : public CThreadBase
{
public:
	CAlbumRequest(const std::string &Title = "", int ProgressStep = 1);

	void StartThread();
	void SetIndex(int Index);
	int Index() const { return m_ProgressBar.Index(); }
	bool Complete() const { return m_Complete; }
	int Progress() const { return m_CurrentProgress; }
	bool NeedsUpdate();
	void ForceUpdate();

protected:
	virtual void ThreadProc() override;

private:
	CProgressBar m_ProgressBar;
	std::string m_Title;
	int m_CurrentProgress = 0;
	int m_ProgressStep = 0;
	bool m_Complete = false;
	bool m_NeedsUpdate = false;
};

#endif
