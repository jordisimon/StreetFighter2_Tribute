#pragma once
#include "Color.h"
#include "Point.h"
#include "SDL\include\SDL_rect.h"

class ICollitionListener;

class Collider
{
public:
	Collider(const SDL_Rect& r, ICollitionListener* lis, const Color& col);
	virtual ~Collider();

	SDL_Rect colliderRect;
	bool moved;
	Color color;
	ICollitionListener* listener;
	bool toDelete;

	void SetPosition(const iPoint& pos);
};

