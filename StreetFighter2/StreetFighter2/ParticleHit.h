#pragma once
#include "Particle.h"

class ParticleHit :	public Particle
{
private:
	AnimationCollider animation;

public:
	ParticleHit(ParticleType typ,const fPoint& pos, Direction dir, SDL_Texture* text, const AnimationCollider& runAnim);
	~ParticleHit();

	bool UpdateState();
};

