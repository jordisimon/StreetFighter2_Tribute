#pragma once
#include <vector>
#include "Sprite.h"
#include "Timer.h"

class Animation
{
protected:
	float currentFrame;
	int validFrame;
	int framesSize; //To avoid query vector size each frame 
	float currentSpeed; //times per second executed (or 1/duration in seconds)

	//Used to change speed for a short period
	bool speedAltered;
	float originalSpeed;
	Timer timer;

	void ResetOriginalSpeed();
	virtual void OnRestart() {};

public:
	
	bool loop;
	unsigned int loopsCompleted;
	bool forward;
	std::vector<Sprite> frames;

	Animation();
	~Animation();
	
	void SetFramesSize();
	void SetSpeed(float sp);
	void SetDuration(float dur);
	virtual void ResetAnimation();
	virtual void UpdateCurrentFrame();
	bool HasFinished() const;
	const Sprite& GetFrame() const;
	int GetCurrentFrameIndex() const;
	void ChangeSpeedTemporal(float ratio, int time);
};

