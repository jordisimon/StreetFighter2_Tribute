#include "Collider.h"
#include "SDL\include\SDL_rect.h"


Collider::Collider(ColliderType t, const SDL_Rect& r, ICollitionListener* lis, const Color& col) :
	type{ t }, colliderRect { r.x, r.y, r.w, r.h }, listener { lis }, color { col }, toDelete { false }, changed { true }
{
}


Collider::~Collider()
{
}

void Collider::SetRect(const SDL_Rect& rect)
{
	changed = (colliderRect.x != rect.x)
		|| (colliderRect.y != rect.y)
		|| (colliderRect.w != rect.w)
		|| (colliderRect.h != rect.h);

	colliderRect = rect;
}

void Collider::SetPosition(const iPoint & pos)
{
	changed = (colliderRect.x != pos.x)
		|| (colliderRect.y != pos.y);

	colliderRect.x = pos.x;
	colliderRect.y = pos.y;
}
