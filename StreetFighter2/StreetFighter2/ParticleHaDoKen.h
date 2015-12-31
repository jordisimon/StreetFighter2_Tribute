#pragma once
#include "Particle.h"

class Collider;

class ParticleHaDoKen :	public Particle
{
private:
	AnimationCollider runAnimation;
	AnimationCollider endAnimation;
	fPoint speed;
	int damage;

public:
	ParticleHaDoKen(ParticleType typ, fPoint pos, Direction dir, SDL_Texture* text, const AnimationCollider& runAnim, const AnimationCollider& endAnim);
	~ParticleHaDoKen();

	bool UpdateState();

	void OnCollitionEnter(Collider* colA, Collider* colB);
	void OnCollitionExit(Collider* colA, Collider* colB);
};

