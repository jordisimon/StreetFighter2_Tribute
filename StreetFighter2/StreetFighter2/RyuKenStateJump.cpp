#include "RyuKenStateJump.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"



RyuKenStateJump::RyuKenStateJump(RyuKen* p) : RyuKenState{ p }
{
	jumpSpeed = (float)character->jumpVSpeed;
}


RyuKenStateJump::~RyuKenStateJump()
{
}

void RyuKenStateJump::OnEnter()
{
	character->currentAnimation = &character->jump;
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
}

void RyuKenStateJump::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}

CharacterState * RyuKenStateJump::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	character->nextPosition.y -= jumpSpeed;
	jumpSpeed += character->gravity;
	
	if (character->nextPosition.y > character->groundLevel)
	{
		character->nextPosition.y = (float)character->groundLevel;
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}
