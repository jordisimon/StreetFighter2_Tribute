#include "ParticleHaDoKen.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTime.h"
#include "Collider.h"
#include "ColliderType.h"
#include "ParticleInfo.h"


ParticleHaDoKen::ParticleHaDoKen(ParticleType typ, const fPoint& pos, Direction dir, SDL_Texture* text, const AnimationCollider& runAnim, const AnimationCollider& endAnim)
	: ParticleAttack(typ, pos, dir, text), runAnimation {runAnim}, endAnimation {endAnim}
{
	runAnimation.listener = this;
	runAnimation.ResetAnimation();
	runAnimation.InitColliders(position, direction);
	currentAnimation = &runAnimation;

	switch (type)
	{
	case ParticleType::LIGHT_HADOKEN:
		strength = AttackStrength::LIGHT;
		speed = 110;
		break;
	case ParticleType::MEDIUM_HADOKEN:
		strength = AttackStrength::MEDIUM;
		speed = 130;
		break;
	case ParticleType::HARD_HADOKEN:
		strength = AttackStrength::HARD;
		speed = 150;
		break;
	default:
		break;
	}

	if (direction == Direction::LEFT)
		speed *= -1;
}


ParticleHaDoKen::~ParticleHaDoKen()
{
}

bool ParticleHaDoKen::UpdateState()
{
	if (currentAnimation->HasFinished())
	{
		toDelete = true;
	}
	else
	{
		position.x += speed * servicesManager->time->frameTimeSeconds;
		currentAnimation->UpdateCurrentFrame(position, direction);
	}
	return true;
}

void ParticleHaDoKen::OnCollitionEnter(Collider * colA, Collider * colB)
{
	if (currentAnimation != &endAnimation)
	{
		runAnimation.CleanUpColliders();
		endAnimation.ResetAnimation();
		currentAnimation = &endAnimation;
	}
}

void ParticleHaDoKen::OnCollitionExit(Collider * colA, Collider * colB)
{
	if (colB->type == ColliderType::SCENE_BOX)
	{
		colA->toDelete = true;
		toDelete = true;
	}
}

const AttackInfo ParticleHaDoKen::GetAttackInfo() const
{
	AttackInfo attackInfo;

	attackInfo.type = AttackType::SPECIAL;
	attackInfo.strength = strength;

	switch (strength)
	{
	case AttackStrength::LIGHT:
		attackInfo.damage = 19;
		attackInfo.backMovement = 30;
		attackInfo.backSpeed = 50;
		break;
	case AttackStrength::MEDIUM:
		attackInfo.damage = 19;
		attackInfo.backMovement = 30;
		attackInfo.backSpeed = 50;
		break;
	case AttackStrength::HARD:
		attackInfo.damage = 19;
		attackInfo.backMovement = 30;
		attackInfo.backSpeed = 50;
		break;
	default:
		break;
	}

	return attackInfo;
}
