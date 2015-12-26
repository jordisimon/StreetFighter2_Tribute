#pragma once
#include "Point.h"
#include "Animation.h"
#include "Direction.h"

struct SDL_Texture;

class Particle
{
protected:
	SDL_Texture* texture = nullptr;
	Animation* animation = nullptr;
	fPoint position;
	Direction direction;

public:
	bool toDelete;

	Particle(const fPoint& pos, Direction dir, SDL_Texture* text);
	virtual ~Particle();

	virtual bool UpdateState() { return true; };
	virtual bool Draw();
};

