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
#include "RyuKenStateKnockdown.h"

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

CharacterState * RyuKenStateCrouch::DealHit(Collider * collider, const fRect& intersectionRect)
{
	if (collider->type == ColliderType::CHARACTER_ATTACK)
	{
		AttackInfo attackInfo = ((Character*)collider->listener)->GetAttackInfo();
		if (!defending)
		{
			ManageHitImpacted(attackInfo, intersectionRect, true, false, true);
		}
		else
		{
			//Crouch blocking can not block aerial attacks
			switch (attackInfo.type)
			{
			case AttackType::J_L_PUNCH:
			case AttackType::J_M_PUNCH:
			case AttackType::J_H_PUNCH:
			case AttackType::F_J_L_PUNCH:
			case AttackType::F_J_M_PUNCH:
			case AttackType::F_J_H_PUNCH:
			case AttackType::J_L_KICK:
			case AttackType::J_M_KICK:
			case AttackType::J_H_KICK:
			case AttackType::F_J_L_KICK:
			case AttackType::F_J_M_KICK:
			case AttackType::F_J_H_KICK:
				return ManageHitImpacted(attackInfo, intersectionRect, true, false, true);
				break;
			}

			return ManageHitBlocked(attackInfo, intersectionRect, true);
		}

	}
	else if (collider->type == ColliderType::PARTICLE_ATTACK)
	{
		AttackInfo attackInfo = ((ParticleAttack*)collider->listener)->GetAttackInfo();
		if (!defending)
		{
			ManageHitImpacted(attackInfo, intersectionRect, false, true, true);
		}
		else
		{
			ManageHitBlocked(attackInfo, intersectionRect, false);
		}
	}

	return nullptr;
}
