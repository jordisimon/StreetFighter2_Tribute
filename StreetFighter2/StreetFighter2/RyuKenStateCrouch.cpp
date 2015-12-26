#include "RyuKenStateCrouch.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateFWalk.h"
#include "RyuKenStateBWalk.h"
#include "RyuKenStateAttack.h"

State* RyuKenStateCrouch::ProcessMovement(Direction dir)
{
	if (dir == character->direction)
		return new RyuKenStateFWalk(character);
	else
		return new RyuKenStateBWalk(character);
}

State * RyuKenStateCrouch::ProcessActions(std::vector<CommandAction> actions)
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

State * RyuKenStateCrouch::ProcessStates(std::vector<CommandState> states)
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
			return ProcessMovement(Direction::LEFT);
			break;

		case CommandState::MOVE_RIGHT:
			return ProcessMovement(Direction::RIGHT);
			break;
		}
	}

	if (!keepCrouching)
	{
		return new RyuKenStateIdle(character);
	}
	return nullptr;
}

RyuKenStateCrouch::RyuKenStateCrouch(RyuKen* p, bool def) : RyuKenState{ p }, defending { def }
{
}


RyuKenStateCrouch::~RyuKenStateCrouch()
{
}

void RyuKenStateCrouch::OnEnter()
{
	character->currentAnimation = &character->crouch;
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
}

void RyuKenStateCrouch::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}

State * RyuKenStateCrouch::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}
