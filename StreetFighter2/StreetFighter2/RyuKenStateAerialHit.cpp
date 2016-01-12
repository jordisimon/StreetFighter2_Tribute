#include "RyuKenStateAerialHit.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateStunned.h"
#include "RyuKenStateFinish.h"


RyuKenStateAerialHit::RyuKenStateAerialHit(RyuKen* p) : RyuKenState{ p }, playerWin{ -1 }
{
	character->currentJumpSpeed = (float)character->jumpVSpeed;

	if (character->direction == Direction::LEFT)
		direction = Direction::RIGHT;
	else
		direction = Direction::LEFT;
}


RyuKenStateAerialHit::~RyuKenStateAerialHit()
{
}

void RyuKenStateAerialHit::OnEnter()
{
	character->ClearActionsSequence();
	character->currentAnimation = &character->aHit;

	RyuKenState::OnEnter();
}

CharacterState * RyuKenStateAerialHit::UpdateState()
{
	RyuKenState::UpdateState();

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	character->MoveXPosition(direction, character->bJumpHSpeed);

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

CharacterState * RyuKenStateAerialHit::RoundFinished(int playerWin)
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
