#include "ParticleStunned.h"



ParticleStunned::ParticleStunned(ParticleType typ, const fPoint& pos, Direction dir, SDL_Texture* text, const AnimationCollider& runAnim)
	: Particle(typ, pos, dir, text), animation{ runAnim }
{
	animation.ResetAnimation();
	currentAnimation = &animation;
}


ParticleStunned::~ParticleStunned()
{
}

bool ParticleStunned::UpdateState()
{
	currentAnimation->UpdateCurrentFrame(position, direction);
	return true;
}
