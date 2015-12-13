#include "Sprite.h"



Sprite::Sprite() : rect{ 0, 0, 0, 0 }, offset{ 0, 0 }
{
}

Sprite::Sprite(const SDL_Rect& r, const iPoint& o) : rect{ r.x, r.y, r.w, r.h }, offset{ o }
{
}

Sprite::~Sprite()
{
}

const iPoint Sprite::GetBlitPosition(const iPoint& position, const Direction direction) const
{
	if (direction == Direction::RIGHT)
		return position - offset;
	else
	{
		iPoint result;
		result.x = position.x + offset.x - rect.w;
		result.y = position.y - offset.y;
		return result;
	}

}


