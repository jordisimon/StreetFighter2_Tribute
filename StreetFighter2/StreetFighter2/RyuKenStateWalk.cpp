#include "RyuKenStateWalk.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateAttack.h"
#include "RyuKenStateShoulderToss.h"
#include "RyuKenStateBackRoll.h"
#include "RyuKenStateBlocking.h"
#include "RyuKenStateKyaku.h"
#include "RyuKenStateHadoken.h"

RyuKenStateWalk::RyuKenStateWalk(RyuKen* p, Direction direction) : RyuKenState{p}
{
	forward = direction == character->direction;
}

RyuKenStateWalk::RyuKenStateWalk(RyuKen * p, bool f) : RyuKenState{ p }, forward{ f }
{
}


RyuKenStateWalk::~RyuKenStateWalk()
{
}

void RyuKenStateWalk::OnEnter()
{
	if (forward)
		character->currentAnimation = &character->fWalk;
	else
		character->currentAnimation = &character->bWalk;

	RyuKenState::OnEnter();
}

CharacterState * RyuKenStateWalk::ProcessActions(std::vector<CommandAction> actions)
{
	bool closeRange = character->RivalDistanceLowerThan((character->fMargin * 2) + 10);
	for (const auto& command : actions)
	{
		switch (command)
		{
		case CommandAction::L_PUNCH:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_L_PUNCH);
			else
				return new RyuKenStateAttack(character, AttackType::L_PUNCH);
			break;
		case CommandAction::M_PUNCH:
			if (closeRange)
				if (forward && character->rival->position.y >= character->groundLevel)
					return new RyuKenStateShoulderToss(character, character->direction);
				else
					return new RyuKenStateAttack(character, AttackType::F_M_PUNCH);
			else
				return new RyuKenStateAttack(character, AttackType::M_PUNCH);
			break;
		case CommandAction::H_PUNCH:
			if (closeRange)
				if (forward && character->rival->position.y >= character->groundLevel)
					return new RyuKenStateShoulderToss(character, character->direction);
				else
					return new RyuKenStateAttack(character, AttackType::F_H_PUNCH);
			else
				return new RyuKenStateAttack(character, AttackType::H_PUNCH);
			break;
		case CommandAction::L_KICK:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_L_KICK);
			else
				return new RyuKenStateAttack(character, AttackType::L_KICK);
			break;
		case CommandAction::M_KICK:
			if (closeRange)
				if (forward && character->rival->position.y >= character->groundLevel)
					return new RyuKenStateBackRoll(character, character->direction);
				else
					return new RyuKenStateAttack(character, AttackType::F_M_KICK);
			else
				return new RyuKenStateAttack(character, AttackType::M_KICK);
			break;
		case CommandAction::H_KICK:
			if (closeRange)
				if (forward && character->rival->position.y >= character->groundLevel)
					return new RyuKenStateBackRoll(character, character->direction);
				else
					return new RyuKenStateAttack(character, AttackType::F_H_KICK);
			else
				return new RyuKenStateAttack(character, AttackType::H_KICK);
			break;
		}
	}
	return nullptr;
}

CharacterState * RyuKenStateWalk::ProcessStates(std::vector<CommandState> states)
{
	bool keepWalking = false;
	bool walkingForward = false;
	Direction dir;

	for (const auto& command : states)
	{
		switch (command)
		{
		case CommandState::MOVE_LEFT:
			keepWalking = true;
			walkingForward = (character->direction == Direction::LEFT);
			dir = Direction::LEFT;
			break;

		case CommandState::MOVE_RIGHT:
			keepWalking = true;
			walkingForward = (character->direction == Direction::RIGHT);
			dir = Direction::RIGHT;
			break;
		}
	}

	if (!keepWalking)
	{
		return new RyuKenStateIdle(character);
	}
	else
	{
		if (forward != walkingForward)
		{
			return new RyuKenStateWalk(character, dir);
		}
	}
	return nullptr;
}

CharacterState * RyuKenStateWalk::UpdateState()
{
	RyuKenState::UpdateState();

	if (!forward && ((character->rival->isAttacking && character->RivalDistanceLowerThan(150))
		|| (character->RivalParticleDistanceLowerThan(150))))
		return new RyuKenStateBlocking(character);

	switch (character->direction)
	{
	case Direction::LEFT:
		if (forward)
			character->MoveXPosition(Direction::LEFT, character->fSpeed);
		else
			character->MoveXPosition(Direction::RIGHT, character->bSpeed);
		break;
	case Direction::RIGHT:
		if (forward)
			character->MoveXPosition(Direction::RIGHT, character->fSpeed);
		else
			character->MoveXPosition(Direction::LEFT, character->bSpeed);
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}

CharacterState * RyuKenStateWalk::DoSpecialAction(const CharacterSpecialAttack & type)
{
	const RyuKenSpecialAttack& specialType = (RyuKenSpecialAttack&)type;

	switch (specialType.type)
	{
	case RyuKenSpecialAttackType::L_KYAKU:
		return new RyuKenStateKyaku(character, AttackStrength::LIGHT);

	case RyuKenSpecialAttackType::M_KYAKU:
		return new RyuKenStateKyaku(character, AttackStrength::MEDIUM);

	case RyuKenSpecialAttackType::H_KYAKU:
		return new RyuKenStateKyaku(character, AttackStrength::HARD);

	case RyuKenSpecialAttackType::L_HADOKEN:
		return new RyuKenStateHadoken(character, AttackStrength::LIGHT);

	case RyuKenSpecialAttackType::M_HADOKEN:
		return new RyuKenStateHadoken(character, AttackStrength::MEDIUM);

	case RyuKenSpecialAttackType::H_HADOKEN:
		return new RyuKenStateHadoken(character, AttackStrength::HARD);
	}

	return nullptr;
}

void RyuKenStateWalk::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	if (forward)
		character->MoveXPosition(character->direction, character->pSpeed);
}
