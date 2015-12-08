#pragma once
#include <vector>
#include "Sprite.h"

class Animation
{
public:
	float speed;
	std::vector<Sprite> frames;

private:
	float current_frame;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	~Animation() {};

	const Sprite& GetCurrentFrame();
	const Sprite& GetFrame() const;

	void ResetAnimation();
	void NextFrame();
	void PriorFrame();
};

