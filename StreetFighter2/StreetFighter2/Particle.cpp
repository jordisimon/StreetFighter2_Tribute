#include "Particle.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "Sprite.h"

Particle::Particle(const iPoint& pos, Direction dir, SDL_Texture* text) : toDelete{ false }, position{ pos }, direction{ dir }, texture{ text }
{
}


Particle::~Particle()
{
}

bool Particle::Draw()
{
	servicesManager->render->Blit(texture, animation->GetFrame().GetBlitPosition(position, direction), &(animation->GetFrame().rect), 1.0f, direction);
	return true;
}
