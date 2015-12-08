#pragma once
#include <vector>
#include "Sprite.h"

class Animation
{
public:
	float speed;
	std::vector<SDL_Rect> frames;

private:
	float current_frame;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	~Animation();
};

