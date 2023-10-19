#include "ThreadBase.h"

CThreadBase::CThreadBase(bool Detach)
		: m_Detach(Detach)
{
}

CThreadBase::~CThreadBase()
{
	StopThread();
}

void CThreadBase::StartThread()
{
	m_ShouldRun = true;

	m_Thread = std::thread([this]
												 { this->ThreadProc(); });

	if (m_Detach)
	{
		Detach();
	}
}

void CThreadBase::Detach()
{
	if (m_Thread.joinable())
	{
		m_Thread.detach();
	}
}

void CThreadBase::StopThread()
{
	m_ShouldRun = false;

	if (m_Thread.joinable())
	{
		m_Thread.join();
	}
}
