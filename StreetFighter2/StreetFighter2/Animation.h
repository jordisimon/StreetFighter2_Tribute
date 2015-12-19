#pragma once
#include <vector>
#include "Sprite.h"

class Animation
{
private:
	float current_frame;

public:
	float speed;
	bool loop;
	Sprite emptySprite;
	std::vector<Sprite> frames;

	Animation();
	~Animation();
	
	void ResetAnimation();
	void UpdateCurrentFrame();
	bool HasFinished() const;
	const Sprite& GetFrame() const;
	void NextFrame();
	void PriorFrame();
};

