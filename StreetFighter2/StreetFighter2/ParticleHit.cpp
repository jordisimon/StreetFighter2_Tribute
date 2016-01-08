#include "ParticleHit.h"



ParticleHit::ParticleHit(ParticleType typ, const fPoint& pos, Direction dir, SDL_Texture* text, const AnimationCollider& runAnim)
	: Particle(typ, pos, dir, text), animation{ runAnim }
{
	animation.ResetAnimation();
	currentAnimation = &animation;
}


ParticleHit::~ParticleHit()
{
}

bool ParticleHit::UpdateState()
{
	if (currentAnimation->HasFinished())
	{
		toDelete = true;
	}
	else
	{
		currentAnimation->UpdateCurrentFrame(position, direction);
	}
	return true;
}
