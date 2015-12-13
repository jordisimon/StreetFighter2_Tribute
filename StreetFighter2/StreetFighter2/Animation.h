#pragma once
#include <vector>
#include "Sprite.h"

class Animation
{
public:
	float speed;
	bool loop;
	Sprite emptySprite;
	std::vector<Sprite> frames;

private:
	float current_frame;

public:
	Animation();
	~Animation();
	
	void ResetAnimation();
	void UpdateCurrentFrame();
	bool HasFinished() const;
	const Sprite& GetFrame() const;
	void NextFrame();
	void PriorFrame();
};

