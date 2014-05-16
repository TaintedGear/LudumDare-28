#include "Timer.h"

Timer::Timer() : m_started(false), m_paused(false),
	m_startTicks(0), m_pausedTicks(0)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	//Get the current time
	m_startTicks = SDL_GetTicks();
	
	//Set timer state to started
	m_started = true;

	//Reset the paused ticks
	m_pausedTicks = 0;
}

void Timer::Stop()
{
	//reset the timer
	m_startTicks = 0;
	m_pausedTicks = 0;
	m_started = false;
	m_paused = false;
}

void Timer::Pause()
{
	if(m_started && !m_paused)
	{
		//set the timer state to pause
		m_paused = true;
		
		//get the amount of ticks at this time
		m_pausedTicks = SDL_GetTicks();

		//reset the start ticks
		m_startTicks = 0;
	}
}

void Timer::Unpause()
{
	if(m_started && m_paused)
	{
		//set the timer state to unpaused
		m_paused = false;

		//get the start ticks from the current ticks - the paused ticks
		m_startTicks = SDL_GetTicks() - m_pausedTicks;

		//reset the paused ticks
		m_pausedTicks = 0;
	}
}

Uint32 Timer::GetTicks()
{
	if(m_started)
	{
		if(m_paused)
		{
			//Return the time at which it paused
			return m_pausedTicks;
		}
		else
		{
			//Return the current time
			return SDL_GetTicks() - m_startTicks;
		}
	}

	return 0;
}

bool Timer::IsStarted()
{
	return m_started;
}

bool Timer::IsPaused()
{
	return m_paused;
}