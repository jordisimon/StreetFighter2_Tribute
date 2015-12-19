#pragma once

class Timer
{
private: 
	unsigned int interval;
	unsigned int timeout;

	bool paused;
	unsigned int pauseTime;

public:
	Timer(unsigned int i, bool startPaused = false);
	~Timer() {};

	void SetNewInterval(unsigned int i);
	void Reset();
	bool Reached();
	void Pause();
	void Resume();
};

