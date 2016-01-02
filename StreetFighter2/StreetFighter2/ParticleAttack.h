#pragma once
#include "Particle.h"
#include "AttackInfo.h"


class ParticleAttack : public Particle
{
public:
	ParticleAttack(ParticleType typ, const fPoint& pos, Direction dir, SDL_Texture* text);
	~ParticleAttack();

	virtual AttackInfo GetAttackInfo() { return AttackInfo(); }
};

