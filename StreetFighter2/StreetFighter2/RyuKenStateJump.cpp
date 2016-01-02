#include "RyuKenStateJump.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateAerialAttack.h"

RyuKenStateJump::RyuKenStateJump(RyuKen* p) : RyuKenState{ p }
{
	character->currentJumpSpeed = (float)character->jumpVSpeed;
}


RyuKenStateJump::~RyuKenStateJump()
{
}

void RyuKenStateJump::OnEnter()
{
	character->currentAnimation = &character->jump;
	RyuKenState::OnEnter();
}

CharacterState * RyuKenStateJump::ProcessActions(std::vector<CommandAction> actions)
{
	for (const auto& command : actions)
	{
		switch (command)
		{
		case CommandAction::L_PUNCH:
			return new RyuKenStateAerialAttack(character, AttackType::J_L_PUNCH);
			break;
		case CommandAction::M_PUNCH:
			return new RyuKenStateAerialAttack(character, AttackType::J_M_PUNCH);
			break;
		case CommandAction::H_PUNCH:
			return new RyuKenStateAerialAttack(character, AttackType::J_H_PUNCH);
			break;
		case CommandAction::L_KICK:
			return new RyuKenStateAerialAttack(character, AttackType::J_L_KICK);
			break;
		case CommandAction::M_KICK:
			return new RyuKenStateAerialAttack(character, AttackType::J_M_KICK);
			break;
		case CommandAction::H_KICK:
			return new RyuKenStateAerialAttack(character, AttackType::J_H_KICK);
			break;
		}
	}
	return nullptr;
}

CharacterState * RyuKenStateJump::UpdateState()
{
	RyuKenState::UpdateState();

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	
	if (character->nextPosition.y >= character->groundLevel)
	{
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}
