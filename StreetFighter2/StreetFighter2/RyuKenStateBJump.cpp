#include "RyuKenStateBJump.h"
#include "RyuKen.h"
#include "ServicesManager.h"
#include "ServiceTime.h"
#include "RyuKenStateIdle.h"


RyuKenStateBJump::RyuKenStateBJump(RyuKen* p) : RyuKenState{ p }
{
	jumpSpeed = (float)character->jumpVSpeed;
}


RyuKenStateBJump::~RyuKenStateBJump()
{
}

void RyuKenStateBJump::OnEnter()
{
	character->currentAnimation = &character->bJump;
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
}

void RyuKenStateBJump::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}

State * RyuKenStateBJump::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	character->position.y -= jumpSpeed;
	jumpSpeed += character->gravity;

	switch (character->direction)
	{
	case Direction::LEFT:
		character->position.x += (character->fJumpHSpeed) * (servicesManager->time->frameTimeSeconds);
		break;
	case Direction::RIGHT:
		character->position.x -= (character->fJumpHSpeed) * (servicesManager->time->frameTimeSeconds);
	}

	//TODO: remove 220 hardcoded
	if (character->position.y > 220)
	{
		character->position.y = 220;
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}
