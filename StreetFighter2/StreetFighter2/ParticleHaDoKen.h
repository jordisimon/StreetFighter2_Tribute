#pragma once
#include "ParticleAttack.h"
#include "AttackInfo.h"

class Collider;

class ParticleHaDoKen :	public ParticleAttack
{
private:
	AnimationCollider runAnimation;
	AnimationCollider endAnimation;
	AttackStrength strength;
	int speed;

public:
	ParticleHaDoKen(ParticleType typ, fPoint pos, Direction dir, SDL_Texture* text, const AnimationCollider& runAnim, const AnimationCollider& endAnim);
	~ParticleHaDoKen();

	bool UpdateState();

	void OnCollitionEnter(Collider* colA, Collider* colB);
	void OnCollitionExit(Collider* colA, Collider* colB);

	const AttackInfo GetAttackInfo() const;
};

