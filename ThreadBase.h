#ifndef _THREAD_BASE_H
#define _THREAD_BASE_H

#include <thread>
#include <mutex>

class CThreadBase
{
public:
	CThreadBase(bool Detach);
	~CThreadBase();

	void Detach();

protected:
	virtual void ThreadProc() = 0;

	virtual void StopThread();
	virtual void StartThread();

	bool m_ShouldRun{false};
	bool m_Detach{false};
	std::thread m_Thread;
	std::mutex m_Mutex;
};

#endif
