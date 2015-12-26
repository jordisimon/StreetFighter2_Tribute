#include "RyuKenStateJump.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"



RyuKenStateJump::RyuKenStateJump(RyuKen* p) : RyuKenState{ p }
{
	jumpSpeed = (float)character->jumpSpeed;
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

State * RyuKenStateJump::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	character->position.y -= jumpSpeed;
	jumpSpeed += character->gravity;
	

	//TODO: remove 220 hardcoded
	if (character->position.y > 220)
	{
		character->position.y = 220;
		return new RyuKenStateIdle(character);
	}
	/*character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	if (character->currentAnimation->HasFinished())
		return new RyuKenStateIdle(character);*/
	return nullptr;
}
