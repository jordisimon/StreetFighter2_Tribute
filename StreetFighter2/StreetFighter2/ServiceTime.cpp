#include "ServiceTime.h"
#include "SDL\include\SDL_timer.h"

ServiceTime::ServiceTime()
{
}


ServiceTime::~ServiceTime()
{
}

bool ServiceTime::Start()
{
	Update();
	return true;
}

void ServiceTime::Update()
{
	lastTime = currentTime;
	currentTime = SDL_GetTicks();
	frameTimeMilliseconds = currentTime - lastTime;
	frameTimeSeconds = (float)frameTimeMilliseconds / 1000;
}
