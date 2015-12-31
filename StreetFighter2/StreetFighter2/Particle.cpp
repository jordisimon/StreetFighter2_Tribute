#include "Particle.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "Sprite.h"

Particle::Particle(ParticleType typ, const fPoint& pos, Direction dir, SDL_Texture* text) : type{ typ }, toDelete { false }, position{ pos }, direction{ dir }, texture{ text }
{
}


Particle::~Particle()
{
}

bool Particle::Draw() const
{
	if (currentAnimation != nullptr)
		servicesManager->render->BlitScene(texture, currentAnimation->GetFrame().GetRectPosition(position, direction), (currentAnimation->GetFrame().rect), 1.0f, direction);
	return true;
}
