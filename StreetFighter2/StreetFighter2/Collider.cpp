#include "Collider.h"


Collider::Collider(ColliderType t, const fRect& r, ICollitionListener* lis, const Color& col, bool act) :
	type{ t }, colliderRect{ r.x, r.y, r.w, r.h }, listener{ lis }, color{ col }, active{ act }, toDelete {	false }, changed{ true }
{
}


Collider::~Collider()
{
}

void Collider::SetRect(const fRect& rect)
{
	changed = (colliderRect.x != rect.x)
		|| (colliderRect.y != rect.y)
		|| (colliderRect.w != rect.w)
		|| (colliderRect.h != rect.h);

	colliderRect = rect;
}

void Collider::SetPosition(const fPoint & pos)
{
	changed = (colliderRect.x != pos.x)
		|| (colliderRect.y != pos.y);

	colliderRect.x = pos.x;
	colliderRect.y = pos.y;
}
