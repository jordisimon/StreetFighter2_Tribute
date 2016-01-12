#include "RyuKenStateIdle.h"
#include "RyuKen.h"
#include "CommandData.h"
#include "RyuKenStateWalk.h"
#include "RyuKenStateCrouch.h"
#include "RyuKenStateAttack.h"
#include "RyuKenStateJump.h"
#include "RyuKenStateDiagonalJump.h"

RyuKenStateIdle::RyuKenStateIdle(RyuKen* p) : RyuKenState{ p }
{
}


RyuKenStateIdle::~RyuKenStateIdle()
{
}

void RyuKenStateIdle::OnEnter()
{
	character->currentAnimation = &character->idle;
	RyuKenState::OnEnter();
}

CharacterState * RyuKenStateIdle::ProcessActions(std::vector<CommandAction> actions)
{
	bool closeRange = character->RivalDistanceLowerThan((character->fMargin * 2) + 10);
	for (const auto& command : actions)
	{
		switch (command)
		{
		case CommandAction::L_PUNCH:
			if(closeRange)
				return new RyuKenStateAttack(character, AttackType::F_L_PUNCH);
			else
				return new RyuKenStateAttack(character, AttackType::L_PUNCH);
			break;
		case CommandAction::M_PUNCH:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_M_PUNCH);
			else
				return new RyuKenStateAttack(character, AttackType::M_PUNCH);
			break;
		case CommandAction::H_PUNCH:
			if (closeRange)
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
				return new RyuKenStateAttack(character, AttackType::F_M_KICK);
			else
				return new RyuKenStateAttack(character, AttackType::M_KICK);
			break;
		case CommandAction::H_KICK:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_H_KICK);
			else
				return new RyuKenStateAttack(character, AttackType::H_KICK);
			break;
		}
	}
	return nullptr;
}

CharacterState* RyuKenStateIdle::ProcessStates(std::vector<CommandState> states)
{
	for (const auto& command : states)
	{
		switch (command)
		{
		case CommandState::MOVE_UP:
			return new RyuKenStateJump(character);
			break;
		case CommandState::MOVE_LEFT:
			return new RyuKenStateWalk(character, Direction::LEFT);
			break;

		case CommandState::MOVE_RIGHT:
			return new RyuKenStateWalk(character, Direction::RIGHT);
			break;

		case CommandState::MOVE_DOWN:
			return new RyuKenStateCrouch(character, false);
			break;

		case CommandState::MOVE_UP_LEFT:
			return new RyuKenStateDiagonalJump(character, Direction::LEFT);
			break;

		case CommandState::MOVE_UP_RIGHT:
			return new RyuKenStateDiagonalJump(character, Direction::RIGHT);
			break;

		case CommandState::MOVE_DOWN_LEFT:
			return new RyuKenStateCrouch(character, character->direction == Direction::RIGHT);
			break;
			
		case CommandState::MOVE_DOWN_RIGHT:
			return new RyuKenStateCrouch(character, character->direction == Direction::LEFT);
			break;
		}
	}

	return nullptr;
}


CharacterState* RyuKenStateIdle::UpdateState()
{
	RyuKenState::UpdateState();

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}

