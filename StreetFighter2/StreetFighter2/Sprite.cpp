#include "Sprite.h"

Sprite::Sprite() : rect{ 0.0f, 0.0f, 0.0f, 0.0f }, offset{ 0.0f, 0.0f }
{
}

Sprite::Sprite(const fRect& r, const fPoint& o) : rect{ r.x, r.y, r.w, r.h }, offset{ o }
{
}

Sprite::~Sprite()
{
}

const fPoint Sprite::GetRectPosition(const fPoint& position, const Direction direction) const
{
	if (direction == Direction::RIGHT)
		return position - offset;
	else
	{
		fPoint result;
		result.x = position.x + offset.x - rect.w;
		result.y = position.y - offset.y;
		return result;
	}

}

const fRect Sprite::GetScreenRect(const fPoint & position, const Direction direction) const
{
	const fPoint& pos = GetRectPosition(position, direction);

	return { pos.x, pos.y, rect.w, rect.h };
}


