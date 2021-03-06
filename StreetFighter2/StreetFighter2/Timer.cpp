#include "Timer.h"
#include "SDL\include\SDL_timer.h"


Timer::Timer(): Timer(1000, true)
{
}

Timer::Timer(unsigned int i, bool startPaused) : interval{ i }, paused{ startPaused }
{
	unsigned int now = SDL_GetTicks();
	timeout = now + interval;
	if (paused)
		pauseTime = now;
}

void Timer::SetNewInterval(unsigned int i)
{
	interval = i;
	timeout = SDL_GetTicks() + interval;
}

void Timer::AddElapsedTime(unsigned int i)
{
	timeout -= i;
}

void Timer::Reset()
{
	timeout = SDL_GetTicks() + interval;
}

bool Timer::Reached() const
{
	return (!paused) && SDL_TICKS_PASSED(SDL_GetTicks(), timeout);
}

void Timer::Pause()
{
	if (!paused)
	{
		paused = true;
		pauseTime = SDL_GetTicks();
	}
}

void Timer::Resume()
{
	if (paused)
	{
		timeout += SDL_GetTicks() - pauseTime;
		paused = false;
	}
}
