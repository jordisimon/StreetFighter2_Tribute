#include "ParticleHaDoKen.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTime.h"
#include "Collider.h"
#include "ColliderType.h"
#include "ParticleInfo.h"


ParticleHaDoKen::ParticleHaDoKen(ParticleType typ, fPoint pos, Direction dir, SDL_Texture* text, const AnimationCollider& runAnim, const AnimationCollider& endAnim)
	: ParticleAttack(typ, pos, dir, text), runAnimation {runAnim}, endAnimation {endAnim}
{
	runAnimation.ResetAnimation();
	runAnimation.InitColliders(position, direction);
	currentAnimation = &runAnimation;
	speed.y = 0.0f;

	switch (type)
	{
	case ParticleType::LIGHT_HADOKEN:
		speed.x = 1.0f;
		damage = 10;
		break;
	case ParticleType::MEDIUM_HADOKEN:
		speed.x = 2.0f;
		damage = 20;
		break;
	case ParticleType::HARD_HADOKEN:
		speed.x = 3.0f;
		damage = 30;
		break;
	default:
		break;
	}

	if (direction == Direction::LEFT)
		speed.x *= -1;
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
		position.x += speed.x * servicesManager->time->frameTimeSeconds;
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
