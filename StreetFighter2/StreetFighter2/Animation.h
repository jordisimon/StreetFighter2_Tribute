#pragma once
#include <vector>
#include "Sprite.h"

class Animation
{
protected:
	float current_frame;
	int valid_frame;
	int framesSize; //To avoid query vector size each frame 
	float speed; //times per second executed (or 1/duration in seconds)

	virtual void OnReset() {};

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
	virtual void NextFrame();
	virtual void PriorFrame();
};

