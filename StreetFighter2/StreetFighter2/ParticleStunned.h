#pragma once
#include "Particle.h"
class ParticleStunned :	public Particle
{
private:
	AnimationCollider animation;

public:
	ParticleStunned(ParticleType typ, fPoint pos, Direction dir, SDL_Texture* text, const AnimationCollider& runAnim);
	~ParticleStunned();

	bool UpdateState();
};

