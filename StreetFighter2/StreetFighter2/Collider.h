#pragma once
#include "Color.h"
#include "Point.h"
#include "SDL\include\SDL_rect.h"

class ICollitionListener;
enum class ColliderType; //To be defined in Game specific implementation

class Collider
{
public:
	Collider(ColliderType t, const SDL_Rect& r, ICollitionListener* lis, const Color& col);
	virtual ~Collider();

	ColliderType type;
	SDL_Rect colliderRect;
	ICollitionListener* listener = nullptr;
	Color color;
	bool changed;	
	bool toDelete;
	

	void SetRect(const SDL_Rect& rect);
	void SetPosition(const iPoint& pos);
};

