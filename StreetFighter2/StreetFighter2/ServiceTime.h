#pragma once
#include "Service.h"

class ServiceTime :	public Service
{
private:
	unsigned int lastTime = 0;
	unsigned int currentTime = 0;

public:
	unsigned int frameTimeMilliseconds = 0; //frame time in milliseconds
	float frameTimeSeconds = 0.0f; //frame time in seconds

	ServiceTime();
	~ServiceTime();

	bool Start();
	void Update();

	unsigned int CurrentTime() const { return currentTime; }
};

