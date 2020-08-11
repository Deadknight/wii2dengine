#include "StdAfx.h"

EventRunnable::EventRunnable(Main *mainArg) : CThread()
{
	main = mainArg;
}

#define SLEEP_TIME_FPS_LIMIT 10

bool EventRunnable::run()
{
	//SetThreadName("Event Manager Update Thread");
	uint32 start;
	uint32 last_time = GetTickCount();
	uint32 etime;
	uint32 next_printout = GetTickCount(), next_send = GetTickCount();
	uint32 timeLastFrame = GetTickCount();

	HANDLE hThread = GetCurrentThread();

	while(ThreadState != THREADSTATE_TERMINATE)
	{
		start = GetTickCount();

		uint32 timeCurrentFrame = GetTickCount();
		uint32 timeSinceLastFrame = timeCurrentFrame - timeLastFrame;
		timeLastFrame = timeCurrentFrame;

		main->UpdateEvents(timeSinceLastFrame);

		Sleep(SLEEP_TIME_FPS_LIMIT);
		
		//Update
		last_time = GetTickCount();
		etime = last_time - start;

		if( SLEEP_TIME_FPS_LIMIT > etime )
		{
			WaitForSingleObject( hThread, SLEEP_TIME_FPS_LIMIT - etime );
		}
	}
	return true;
}

#undef SLEEP_TIME_FPS_LIMIT