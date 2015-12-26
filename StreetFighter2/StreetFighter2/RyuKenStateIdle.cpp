#include "RyuKenStateIdle.h"
#include "RyuKen.h"
#include "CommandData.h"
#include "RyuKenStateFWalk.h"
#include "RyuKenStateBWalk.h"
#include "RyuKenStateCrouch.h"
#include "RyuKenStateAttack.h"
#include "RyuKenStateJump.h"


RyuKenStateIdle::RyuKenStateIdle(RyuKen* p) : RyuKenState{ p }
{
}


RyuKenStateIdle::~RyuKenStateIdle()
{
}

void RyuKenStateIdle::OnEnter()
{
	character->currentAnimation = &character->idle;
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
}

void RyuKenStateIdle::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}


State * RyuKenStateIdle::ProcessMovement(Direction dir)
{
	if (dir == character->direction)
		return new RyuKenStateFWalk(character);
	else
		return new RyuKenStateBWalk(character);
}

State * RyuKenStateIdle::ProcessActions(std::vector<CommandAction> actions)
{
	for (const auto& command : actions)
	{
		switch (command)
		{
		case CommandAction::L_PUNCH:
			return new RyuKenStateAttack(character, AttackType::L_PUNCH);
			break;
		case CommandAction::M_PUNCH:
			return new RyuKenStateAttack(character, AttackType::M_PUNCH);
			break;
		case CommandAction::H_PUNCH:
			return new RyuKenStateAttack(character, AttackType::H_PUNCH);
			break;
		case CommandAction::L_KICK:
			return new RyuKenStateAttack(character, AttackType::F_L_KICK);
			break;
		case CommandAction::M_KICK:
			return new RyuKenStateAttack(character, AttackType::F_M_KICK);
			break;
		case CommandAction::H_KICK:
			return new RyuKenStateAttack(character, AttackType::F_H_KICK);
			break;
		}
	}
	return nullptr;
}

State* RyuKenStateIdle::ProcessStates(std::vector<CommandState> states)
{
	for (const auto& command : states)
	{
		switch (command)
		{
		case CommandState::MOVE_UP:
			return new RyuKenStateJump(character);
			break;
		case CommandState::MOVE_LEFT:
			return ProcessMovement(Direction::LEFT);
			break;

		case CommandState::MOVE_RIGHT:
			return ProcessMovement(Direction::RIGHT);
			break;

		case CommandState::MOVE_DOWN:
			return new RyuKenStateCrouch(character, false);
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


State* RyuKenStateIdle::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}
