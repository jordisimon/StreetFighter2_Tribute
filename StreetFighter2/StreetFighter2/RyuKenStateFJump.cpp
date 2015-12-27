#include "RyuKenStateFJump.h"
#include "RyuKen.h"
#include "ServicesManager.h"
#include "ServiceTime.h"
#include "RyuKenStateIdle.h"


RyuKenStateFJump::RyuKenStateFJump(RyuKen* p) : RyuKenState{ p }
{
	jumpSpeed = (float)character->jumpVSpeed;
}


RyuKenStateFJump::~RyuKenStateFJump()
{
}

void RyuKenStateFJump::OnEnter()
{
	character->currentAnimation = &character->fJump;
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
}

void RyuKenStateFJump::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}

State * RyuKenStateFJump::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	character->position.y -= jumpSpeed;
	jumpSpeed += character->gravity;

	switch (character->direction)
	{
	case Direction::LEFT:
		character->position.x -= (character->fJumpHSpeed) * (servicesManager->time->frameTimeSeconds);
		break;
	case Direction::RIGHT:
		character->position.x += (character->fJumpHSpeed) * (servicesManager->time->frameTimeSeconds);
	}

	//TODO: remove 220 hardcoded
	if (character->position.y > 220)
	{
		character->position.y = 220;
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}
