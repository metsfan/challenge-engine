#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	typedef std::function<void(void *)> TimerCallback;

	class CTimer
	{
	public:
		CTimer(int interval, TimerCallback callback, void *callbackObj, bool autoStart);
		void ExecuteCallback();
		void Start();
		void Stop();

		~CTimer(void);

		static VOID CALLBACK TimerProc(PVOID lpParameter, BOOLEAN TimerOrWaitFired);

	private:
		int mInterval;
		TimerCallback mCallback;
		void *mCallbackObj;
		HANDLE mTimer;

		static HANDLE s_TimerQueue;
	};
}

