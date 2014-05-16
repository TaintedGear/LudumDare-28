#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <stdio.h>

class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Pause();
	void Unpause();

	Uint32 GetTicks();

	bool IsStarted();
	bool IsPaused();

private:
	bool m_started,
		m_paused;

	Uint32 m_startTicks,
		m_pausedTicks;
};

#endif