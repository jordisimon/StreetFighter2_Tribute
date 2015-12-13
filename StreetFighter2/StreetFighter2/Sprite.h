#pragma once
#include "Point.h"
#include "Direction.h"
#include "SDL\include\SDL_rect.h"

class Sprite
{
public:
	Sprite();
	Sprite(const SDL_Rect& r, const iPoint& o);
	virtual ~Sprite();

	SDL_Rect rect;
	iPoint offset;

	const iPoint GetBlitPosition(const iPoint& position, const Direction direction) const;
};

