#include "RyuKenStateCrouch.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateWalk.h"
#include "RyuKenStateAttack.h"
#include "RyuKenStateHit.h"
#include "RyuKenStateShoruyken.h"
#include "Collider.h"
#include "ColliderType.h"
#include "ServicesManager.h"
#include "ServiceParticles.h"
#include "ParticleAttack.h"
#include "AttackInfo.h"
#include "ParticleInfo.h"
#include "RyuKenSpecialAttack.h"

CharacterState * RyuKenStateCrouch::ProcessActions(std::vector<CommandAction> actions)
{
	for (const auto& command : actions)
	{
		switch (command)
		{
		case CommandAction::L_PUNCH:
			return new RyuKenStateAttack(character, AttackType::C_L_PUNCH);
			break;
		case CommandAction::M_PUNCH:
			return new RyuKenStateAttack(character, AttackType::C_M_PUNCH);
			break;
		case CommandAction::H_PUNCH:
			return new RyuKenStateAttack(character, AttackType::C_H_PUNCH);
			break;
		case CommandAction::L_KICK:
			return new RyuKenStateAttack(character, AttackType::C_L_KICK);
			break;
		case CommandAction::M_KICK:
			return new RyuKenStateAttack(character, AttackType::C_M_KICK);
			break;
		case CommandAction::H_KICK:
			return new RyuKenStateAttack(character, AttackType::C_H_KICK);
			break;
		}
	}
	return nullptr;
}

CharacterState * RyuKenStateCrouch::ProcessStates(std::vector<CommandState> states)
{
	bool keepCrouching = false;

	for (const auto& command : states)
	{
		switch (command)
		{
		case CommandState::MOVE_DOWN:
			keepCrouching = true;
			break;

		case CommandState::MOVE_DOWN_LEFT:
			keepCrouching = true;
			defending = character->direction == Direction::RIGHT;
			break;

		case CommandState::MOVE_DOWN_RIGHT:
			keepCrouching = true;
			defending = character->direction == Direction::LEFT;			
			break;

		case CommandState::MOVE_LEFT:
			return new RyuKenStateWalk(character, Direction::LEFT);
			break;

		case CommandState::MOVE_RIGHT:
			return new RyuKenStateWalk(character, Direction::RIGHT);
			break;
		}
	}

	if (!keepCrouching)
	{
		return new RyuKenStateIdle(character);
	}
	return nullptr;
}

RyuKenStateCrouch::RyuKenStateCrouch(RyuKen* p, bool def) : RyuKenState{ p }, defending { def }, blocking { false }
{
}


RyuKenStateCrouch::~RyuKenStateCrouch()
{
}

void RyuKenStateCrouch::OnEnter()
{
	character->currentAnimation = &character->crouch;
	RyuKenState::OnEnter();
}

CharacterState * RyuKenStateCrouch::UpdateState()
{
	RyuKenState::UpdateState();

	if (defending && character->isRivalAttacking && character->rivalDistance < 150)
	{
		if (!blocking)
		{
			character->currentAnimation->CleanUpColliders();
			character->currentAnimation = &character->cBlocking;
			character->currentAnimation->InitColliders(character->position, character->direction);
			blocking = true;
		}
	}
	else
	{
		if (blocking)
		{
			character->currentAnimation->CleanUpColliders();
			character->currentAnimation = &character->crouch;
			character->currentAnimation->InitColliders(character->position, character->direction);
			blocking = false;
		}
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}

CharacterState * RyuKenStateCrouch::DoSpecialAction(const CharacterSpecialAttack& type)
{
	const RyuKenSpecialAttack& specialType = (RyuKenSpecialAttack&)type;

	switch (specialType.type)
	{
	case RyuKenSpecialAttackType::L_SHORYUKEN:
		return new RyuKenStateShoruyken(character, AttackStrength::LIGHT);

	case RyuKenSpecialAttackType::M_SHORYUKEN:
		return new RyuKenStateShoruyken(character, AttackStrength::MEDIUM);

	case RyuKenSpecialAttackType::H_SHORYUKEN:
		return new RyuKenStateShoruyken(character, AttackStrength::HARD);
	}

	return nullptr;
}

CharacterState * RyuKenStateCrouch::DealHit(Collider * collider)
{
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

		if (defending)
		{
			particleInfo.type = ParticleType::HIT_BLOCKED;
		}
		else
		{
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
		}

		servicesManager->particles->CreateParticle(particleInfo);

		character->applyToOtherPlayer = true;

	}
	else if (collider->type == ColliderType::PARTICLE_ATTACK)
	{
		ParticleAttack* particle = (ParticleAttack*)collider->listener;
		attackInfo = particle->GetAttackInfo();

		character->applyToOtherPlayer = false;
	}

	character->hitBackwardMovement = attackInfo.backMovement;
	character->hitBackwardSpeed = attackInfo.backSpeed;

	if (!defending)
	{
		character->life -= attackInfo.damage;
		if (character->life < 0)
			character->life = 0;

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

		return new RyuKenStateHit(character, true, false, hitDuration);
	}
		
	return nullptr;
}
