#include "RyuKenStateJump.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateAerialAttack.h"
#include "RyuKenStateFinish.h"

RyuKenStateJump::RyuKenStateJump(RyuKen* p) : RyuKenState{ p, false }, playerWin{ -1 }
{
	character->currentJumpSpeed = (float)character->jumpVSpeed;
}


RyuKenStateJump::~RyuKenStateJump()
{
}

void RyuKenStateJump::OnEnter()
{
	character->SetCurrentAnimation(character->jump);
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
	
	if (character->nextPosition.y >= character->groundLevel)
	{
		character->PlaySfx(character->floorHit2Sfx);
		if (playerWin < 0)
			return new RyuKenStateIdle(character);
		else
			return new RyuKenStateFinish(character, playerWin);
	}

	return nullptr;
}

CharacterState * RyuKenStateJump::RoundFinished(int playerWin)
{
	if (character->life > 0)
	{
		//Store winner (change state when back to ground)
		this->playerWin = playerWin;
		return nullptr;
	}
	else
	{
		return new RyuKenStateFinish(character, playerWin);
	}
}
