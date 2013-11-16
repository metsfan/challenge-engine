#include <Engine/Challenge.h>
#include <Engine/Util/Timer.h>
#include <Mmsystem.h>

namespace challenge
{
	Timer::Timer(TTimerFunc callback, int millis, bool repeat, int accuracy) :
		mCallback(callback),
		mMillis(millis),
		mAccuracy(accuracy),
		mRepeat(repeat)
	{
	}

	Timer::~Timer()
	{
		this->Stop();
	}

	void Timer::Start()
	{
		this->Stop();

		UINT timerParams = mRepeat ? TIME_PERIODIC : TIME_ONESHOT;

		mTimerID = timeSetEvent(mMillis, mAccuracy, Timer::TimerCallback, (DWORD_PTR)this, timerParams);
		if (!mTimerID) {
			throw "Failed to create timer.  We have a serious issue.";
		}
	}

	void Timer::Stop()
	{
		if (mTimerID) {
			timeKillEvent(mTimerID);
			mTimerID = 0;
		}
	}

	void CALLBACK Timer::TimerCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
	{
		Timer *timer = reinterpret_cast<Timer *>(dwUser);
		if (timer->mCallback) {
			timer->mCallback(timer);
		}
	}
};