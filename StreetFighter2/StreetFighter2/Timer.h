#pragma once

class Timer
{
private: 
	unsigned int timeout;
public:
	Timer(unsigned int interval);
	~Timer() {};

	bool Reached();
};

