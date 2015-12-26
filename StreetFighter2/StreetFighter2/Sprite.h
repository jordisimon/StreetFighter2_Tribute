#pragma once
#include "Point.h"
#include "Rect.h"
#include "Direction.h"

class Sprite
{
public:
	fRect rect;
	fPoint offset;

	Sprite();
	Sprite(const fRect& r, const fPoint& o);
	virtual ~Sprite();

	const fPoint GetRectPosition(const fPoint& position, const Direction direction = Direction::RIGHT) const;
	const fRect GetScreenRect(const fPoint& position, const Direction direction = Direction::RIGHT) const;
};

