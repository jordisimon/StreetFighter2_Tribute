#include "Collider.h"
#include "SDL\include\SDL_rect.h"


Collider::Collider(const SDL_Rect& r, ICollitionListener* lis, const Color& col) : 
	colliderRect{ r.x, r.y, r.w, r.h }, listener{ lis }, color{ col }, toDelete{ false }, moved{ true }
{
}


Collider::~Collider()
{
}

void Collider::SetPosition(const iPoint & pos)
{
	colliderRect.x = pos.x;
	colliderRect.y = pos.y;
	moved = true;
}
