#include <algorithm>
#include <chrono>
#include <thread>

#include <signal.h>
#include <slang.h>

#include "AlbumRequest.h"

bool ScreenSizeChanged = false;

static void sigwinch_handler(int sig)
{
	if (sig != SIGWINCH)
		return;
	ScreenSizeChanged = true;
	SLsignal(SIGWINCH, sigwinch_handler);
}

int main(int /*argc*/, const char * /*argv*/[])
{
#ifndef NO_SLANG
	SLutf8_enable(-1);

	SLtt_get_terminfo();

	if (-1 == SLkp_init())
	{
		SLang_verror(0, const_cast<char *>("SLkp_init failed."));
		return 1;
	}

	if (-1 == SLang_init_tty(7, 0, 0))
	{
		SLang_verror(0, const_cast<char *>("SLang_init_tty."));
		return 1;
	}

	SLang_set_abort_signal(NULL);
	if (-1 == SLsmg_init_smg())
	{
		SLang_verror(0, const_cast<char *>("Error initialising SLmsg\n"));
		return 1;
	}

	SLsmg_cls();

	SLsignal(SIGWINCH, sigwinch_handler);

	SLsmg_init_smg();

	SLtt_set_cursor_visibility(0);
	SLtt_flush_output();
	SLsmg_refresh();
#endif

	std::vector<std::shared_ptr<CAlbumRequest>> Requests;

	Requests.push_back(std::make_shared<CAlbumRequest>("Album 1", 5));
	Requests.push_back(std::make_shared<CAlbumRequest>("Album 2", 8));
	Requests.push_back(std::make_shared<CAlbumRequest>("Album 3", 6));

	for (const auto &Request : Requests)
	{
		Request->StartThread();
	}

	while (!Requests.empty())
	{
		bool NeedsUpdate = false;

		for (decltype(Requests)::size_type count = 0; count < Requests.size(); count++)
		{
			Requests[count]->SetIndex(count);
			if (Requests[count]->NeedsUpdate())
			{
				NeedsUpdate = true;
			}
		}

		auto OldSize = Requests.size();

		Requests.erase(std::remove_if(Requests.begin(), Requests.end(),
																	[](std::shared_ptr<CAlbumRequest> &Request)
																	{
																		return Request->Complete();
																	}),
									 Requests.end());

		if (Requests.size() != OldSize)
		{
			NeedsUpdate = true;

			for (decltype(Requests)::size_type count = 0; count < OldSize; count++)
			{
				if (count < Requests.size())
				{
					Requests[count]->ForceUpdate();
				}
				else
				{
					CProgressBar::ClearIndex(count);
				}
			}
		}

		if (NeedsUpdate)
		{
#ifndef NO_SLANG
			SLsmg_refresh();
#endif
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

#ifndef NO_SLANG
	SLsmg_refresh();

	SLsmg_reset_smg();
	SLtt_set_cursor_visibility(1);
	SLang_reset_tty();
#endif

	return 0;
}
