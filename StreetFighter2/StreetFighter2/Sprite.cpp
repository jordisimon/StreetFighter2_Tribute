#include "Sprite.h"



Sprite::Sprite() : rect{ 0, 0, 0, 0 }, offset{ 0, 0 }
{
}

Sprite::Sprite(const SDL_Rect & r, const iPoint & o) : rect{ r.x, r.y, r.w, r.h }, offset{ o }
{
}

Sprite::~Sprite()
{
}
