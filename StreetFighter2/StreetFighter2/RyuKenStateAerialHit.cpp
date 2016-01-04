#include "RyuKenStateAerialHit.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateStunned.h"


RyuKenStateAerialHit::RyuKenStateAerialHit(RyuKen* p) : RyuKenState{ p }
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
		if (character->isStunned)
			return new RyuKenStateStunned(character);
		else
			return new RyuKenStateIdle(character);
	}

	return nullptr;
}
