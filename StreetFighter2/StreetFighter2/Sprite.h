#pragma once
#include "Point.h"
#include "SDL\include\SDL_rect.h"

class Sprite
{
public:
	Sprite();
	Sprite(const SDL_Rect& r, const iPoint& o);
	Sprite(const SDL_Rect&& r, const iPoint&& o);
	virtual ~Sprite();

	SDL_Rect rect;
	iPoint offset;
};

