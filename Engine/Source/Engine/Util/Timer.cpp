#include <Engine/Challenge.h>
#include "Timer.h"
using namespace challenge;

HANDLE CTimer::s_TimerQueue = NULL;

CTimer::CTimer(int interval, TimerCallback callback, void *callbackObj, bool autoStart)
{
	if(!s_TimerQueue) {
		s_TimerQueue = CreateTimerQueue();
	}
	mInterval = interval;
	mCallback = callback;
	mCallbackObj = callbackObj;
	mTimer = NULL;

	if(autoStart) {
		this->Start();
	}

}

void CTimer::Start() 
{
	LARGE_INTEGER liDueTime;

    liDueTime.QuadPart = 0;
	if(mTimer == NULL) {
		BOOL result = CreateTimerQueueTimer(&mTimer, s_TimerQueue, CTimer::TimerProc, this, 0, mInterval, WT_EXECUTEDEFAULT);
		if(!result) {
			printf("Timer failed to initialize\n");
		}
	}
}

void CTimer::Stop() 
{
	//CancelWaitableTimer(mTimer);
	int result = DeleteTimerQueueTimer(s_TimerQueue, mTimer, NULL);

	if(result == 0) {
		DWORD error = GetLastError();
		printf("stop");
	}
	mTimer = NULL;
}


CTimer::~CTimer(void)
{
	this->Stop();
}

void CTimer::ExecuteCallback()
{
	if(mCallback != NULL) {
		mCallback(mCallbackObj);
	}
}

VOID CALLBACK CTimer::TimerProc(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
	CTimer *timer = reinterpret_cast<CTimer *>(lpParameter);
	timer->ExecuteCallback();
}


