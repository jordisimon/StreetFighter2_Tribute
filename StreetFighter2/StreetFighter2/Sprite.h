#pragma once
#include "Point.h"
#include "SDL\include\SDL_rect.h"

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	SDL_Rect rect;
	iPoint offset;
};

