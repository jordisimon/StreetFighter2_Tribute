#include "Timer.h"
#include "SDL\include\SDL_timer.h"


Timer::Timer(unsigned int interval)
{
	timeout = SDL_GetTicks() + interval;
}


bool Timer::Reached()
{
	return SDL_TICKS_PASSED(SDL_GetTicks(), timeout);
}
