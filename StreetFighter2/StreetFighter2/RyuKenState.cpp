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


RyuKenState::RyuKenState(RyuKen* p) : character{ p }
{
}


RyuKenState::~RyuKenState()
{
}

void RyuKenState::OnEnter()
{
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
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
	character->UpdateStunnedParticlePosition();
	character->UpdateYPosition();

	return nullptr;
}

CharacterState * RyuKenState::DealHit(Collider * collider)
{
	bool faceHit = true;
	float hitDuration = 0.0f;
	AttackInfo attackInfo; 

	if (collider->type == ColliderType::CHARACTER_ATTACK)
	{
		Character* enemy = (Character*)collider->listener;
		attackInfo = enemy->GetAttackInfo();

		//Particle only if hit by rival directly
		ParticleInfo particleInfo;
		particleInfo.direction = character->direction;
		particleInfo.position.x = collider->colliderRect.x;
		particleInfo.position.y = collider->colliderRect.y;

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

		character->applyToOtherPlayer = true;
		faceHit = (collider->colliderRect.y < character->position.y - character->height);

	}
	else if (collider->type == ColliderType::PARTICLE_ATTACK)
	{
		ParticleAttack* particle = (ParticleAttack*)collider->listener;
		attackInfo = particle->GetAttackInfo();

		character->applyToOtherPlayer = false;
		faceHit = true;
	}

	character->life -= attackInfo.damage;
	if (character->life < 0)
		character->life = 0;

	if (attackInfo.special)
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

	character->knockdownDamage += attackInfo.damage;
	character->knockdownTimer.Resume();
	character->knockdownTimer.Reset();

	if (!character->isStunned && character->knockdownDamage >= 50)
	{
		if (character->knockdownDamage > 65)
			return new RyuKenStateKnockdown(character, true);
		else
			return new RyuKenStateKnockdown(character, false);
	}
	else
	{
		if (character->position.y >= character->groundLevel)
		{
			character->hitBackwardMovement = attackInfo.backMovement;
			character->hitBackwardSpeed = attackInfo.backSpeed;

			switch (attackInfo.strength)
			{
			case AttackStrength::LIGHT:
				hitDuration = 0.3f;
				break;

			case AttackStrength::MEDIUM:
				hitDuration = 0.6f;
				break;

			case AttackStrength::HARD:
				hitDuration = 0.9f;
				break;
			default:
				break;
			}

			return new RyuKenStateHit(character, false, faceHit, hitDuration);
		}
		else
		{
			return new RyuKenStateAerialHit(character);
		}
	}
}

CharacterState * RyuKenState::MatchFinished(int playerWin)
{
	return new RyuKenStateFinish(character, playerWin);
}
