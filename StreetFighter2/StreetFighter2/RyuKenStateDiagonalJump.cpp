#include "RyuKenStateDiagonalJump.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateAerialAttack.h"


RyuKenStateDiagonalJump::RyuKenStateDiagonalJump(RyuKen* p, Direction dir) : RyuKenState{ p }
{
	character->currentJumpSpeed = (float)character->jumpVSpeed;

	direction = dir;
	forward = character->direction == dir;
	if (forward)
	{
		hSpeed = character->fJumpHSpeed;
	}
	else
	{
		hSpeed = character->bJumpHSpeed;
	}
}


RyuKenStateDiagonalJump::~RyuKenStateDiagonalJump()
{
}

void RyuKenStateDiagonalJump::OnEnter()
{
	if (forward)
		character->currentAnimation = &character->fJump;
	else
		character->currentAnimation = &character->bJump;

	RyuKenState::OnEnter();
}

CharacterState * RyuKenStateDiagonalJump::ProcessActions(std::vector<CommandAction> actions)
{
	for (const auto& command : actions)
	{
		switch (command)
		{
		case CommandAction::L_PUNCH:
			return new RyuKenStateAerialAttack(character, AttackType::F_J_L_PUNCH, direction, forward, hSpeed);
			break;
		case CommandAction::M_PUNCH:
			return new RyuKenStateAerialAttack(character, AttackType::F_J_M_PUNCH, direction, forward, hSpeed);
			break;
		case CommandAction::H_PUNCH:
			return new RyuKenStateAerialAttack(character, AttackType::F_J_H_PUNCH, direction, forward, hSpeed);
			break;
		case CommandAction::L_KICK:
			return new RyuKenStateAerialAttack(character, AttackType::F_J_L_KICK, direction, forward, hSpeed);
			break;
		case CommandAction::M_KICK:
			return new RyuKenStateAerialAttack(character, AttackType::F_J_M_KICK, direction, forward, hSpeed);
			break;
		case CommandAction::H_KICK:
			return new RyuKenStateAerialAttack(character, AttackType::F_J_H_KICK, direction, forward, hSpeed);
			break;
		}
	}
	return nullptr;
}

CharacterState * RyuKenStateDiagonalJump::UpdateState()
{
	RyuKenState::UpdateState();

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	character->MoveXPosition(direction, hSpeed);

	if (character->nextPosition.y >= character->groundLevel)
	{
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}

void RyuKenStateDiagonalJump::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	if (forward)
		character->MoveXPosition(character->direction, character->pSpeed);
}
