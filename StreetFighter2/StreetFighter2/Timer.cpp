#include "Timer.h"
#include "SDL\include\SDL_timer.h"


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

void Timer::Reset()
{
	timeout = SDL_GetTicks() + interval;
}

bool Timer::Reached()
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
