#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class Timer;

	typedef std::function<void(Timer *)> TTimerFunc;

	class Timer
	{
	public:
		Timer(TTimerFunc callback, int millis, bool repeat = false, int accuracy = 100);
		~Timer();

		void SetAccuracy(int acc) { mAccuracy = acc; }

		void Start();
		void Stop();

	private:
		UINT mTimerID;
		TTimerFunc mCallback;
		int mAccuracy;
		int mMillis;
		bool mRepeat;

		static void CALLBACK TimerCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	};
};

