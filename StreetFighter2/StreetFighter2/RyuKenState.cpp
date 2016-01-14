#include "RyuKenState.h"
#include "RyuKen.h"
#include "CommandData.h"
#include "RyuKenStateHit.h"
#include "RyuKenStateAerialHit.h"
#include "RyuKenStateFinish.h"
#include "RyuKenStateKnockdown.h"
#include "Collider.h"
#include "ColliderType.h"
#include "ServicesManager.h"
#include "ServiceParticles.h"
#include "ParticleAttack.h"
#include "AttackInfo.h"
#include "ParticleInfo.h"


RyuKenState::RyuKenState(RyuKen* p, bool changeAnimDir) : character{ p }, changeAnimDirection{ changeAnimDir }
{
}


RyuKenState::~RyuKenState()
{
}

void RyuKenState::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}

CharacterState * RyuKenState::ProcessInput(CommandData * commandData)
{
	//Default behaviour
	CharacterState* result = nullptr;

	if (character->playerNumber == 1)
	{
		result = ProcessActions(commandData->p1Actions);
		if (result == nullptr)
			result = ProcessStates(commandData->p1States);
	}
	else
	{
		result = ProcessActions(commandData->p2Actions);
		if (result == nullptr)
			result = ProcessStates(commandData->p2States);
	}

	return result;
}

CharacterState * RyuKenState::UpdateState()
{
	character->UpdateYPosition();
	character->UpdateCurrentAnimation();

	return nullptr;
}

void RyuKenState::SetDirection(Direction dir)
{
	character->direction = dir;
	if(changeAnimDirection)
		character->animDirection = dir;
}

CharacterState * RyuKenState::DealHit(Collider * collider, const fRect& intersectionRect)
{
	if (collider->type == ColliderType::CHARACTER_ATTACK)
	{
		AttackInfo attackInfo = ((Character*)collider->listener)->GetAttackInfo();
		bool faceHit = (collider->colliderRect.y < character->position.y - character->height);
		return ManageHitImpacted(attackInfo, intersectionRect, true, faceHit, false);
	}
	else if (collider->type == ColliderType::PARTICLE_ATTACK)
	{
		AttackInfo attackInfo = ((ParticleAttack*)collider->listener)->GetAttackInfo();
		return ManageHitImpacted(attackInfo, intersectionRect, false, true, false);
	}

	return nullptr;
}

CharacterState * RyuKenState::ManageHitImpacted(const AttackInfo& attackInfo, const fRect& intersectionRect, bool enemyHit, bool faceHit, bool crouching)
{
	character->applyBackwardMovementToOtherPlayerRatio = 0.0f;

	if (enemyHit)
	{
		//Particle only if hit by rival directly
		ParticleInfo particleInfo;
		particleInfo.direction = character->direction;
		particleInfo.position.x = intersectionRect.x + (intersectionRect.w / 2);
		particleInfo.position.y = intersectionRect.y + (intersectionRect.h / 2);

		switch (attackInfo.strength)
		{
		case AttackStrength::LIGHT:
			if (character->playerNumber == 1)
				particleInfo.type = ParticleType::P2_LHIT;
			else
				particleInfo.type = ParticleType::P1_LHIT;
			break;

		case AttackStrength::MEDIUM:
			if (character->playerNumber == 1)
				particleInfo.type = ParticleType::P2_MHIT;
			else
				particleInfo.type = ParticleType::P1_MHIT;
			break;

		case AttackStrength::HARD:
			if (character->playerNumber == 1)
				particleInfo.type = ParticleType::P2_HHIT;
			else
				particleInfo.type = ParticleType::P1_HHIT;
			break;
		default:
			break;
		}

		servicesManager->particles->CreateParticle(particleInfo);

		character->applyBackwardMovementToOtherPlayerRatio = 1.0f;
	}

	//Play sound fx
	if (attackInfo.type == AttackType::SPECIAL)
		character->PlaySfx(character->hHitSfx);
	else
	{
		switch (attackInfo.strength)
		{
		case AttackStrength::LIGHT:
			character->PlaySfx(character->lHitSfx);
			break;
		case AttackStrength::MEDIUM:
			character->PlaySfx(character->mHitSfx);
			break;
		case AttackStrength::HARD:
			character->PlaySfx(character->hHitSfx);
			break;
		default:
			break;
		}
	}

	//Apply damage
	character->SubstractDamage(attackInfo.damage);

	//Add knockdown damage
	character->knockdownDamage += attackInfo.damage;
	character->knockdownTimer.Resume();
	character->knockdownTimer.Reset();

	//Choose next state
	//If knockdown threshold reached, player throwed
	if (character->knockdownDamage >= 50)
	{
		return new RyuKenStateKnockdown(character, character->direction);
	}
	else
	{
		//If character on the ground
		if (character->position.y >= character->groundLevel)
		{
			//Hard kicks crouching throws character
			if (attackInfo.type == AttackType::C_H_KICK)
			{
				return new RyuKenStateKnockdown(character, character->direction);
			}
			else
			{
				character->hitBackwardMovement = attackInfo.backMovement;
				character->hitBackwardSpeed = attackInfo.backSpeed;

				return new RyuKenStateHit(character, crouching, faceHit, attackInfo.strength);
			}
		}
		else
		{
			return new RyuKenStateAerialHit(character);
		}
	}
}

CharacterState * RyuKenState::ManageHitBlocked(const AttackInfo & attackInfo, const fRect & intersectionRect, bool enemyHit)
{
	character->applyBackwardMovementToOtherPlayerRatio = 0.0f;

	if (enemyHit)
	{
		//Particle only if hit by rival directly
		ParticleInfo particleInfo;
		particleInfo.direction = character->direction;
		particleInfo.position.x = intersectionRect.x + (intersectionRect.w / 2);
		particleInfo.position.y = intersectionRect.y + (intersectionRect.h / 2);
		particleInfo.type = ParticleType::HIT_BLOCKED;
		servicesManager->particles->CreateParticle(particleInfo);

		character->applyBackwardMovementToOtherPlayerRatio = 1.0f;
	}

	//Play sound fx
	character->PlaySfx(character->hitBlockedSfx);

	//If special attack, even when blocking we get some damage (about 25%)
	if (attackInfo.type == AttackType::SPECIAL)
	{
		character->SubstractDamage(attackInfo.damage / 4);
	}

	character->hitBackwardMovement = attackInfo.backMovement;
	character->hitBackwardSpeed = attackInfo.backSpeed;
	return nullptr;
}


CharacterState * RyuKenState::RoundFinished(int playerWin)
{
	return new RyuKenStateFinish(character, playerWin);
}
