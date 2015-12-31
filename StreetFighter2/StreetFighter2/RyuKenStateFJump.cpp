#include "RyuKenStateFJump.h"
#include "RyuKen.h"
#include "ServicesManager.h"
#include "ServiceTime.h"
#include "RyuKenStateIdle.h"


RyuKenStateFJump::RyuKenStateFJump(RyuKen* p) : RyuKenState{ p }
{
	jumpSpeed = (float)character->jumpVSpeed;
	direction = character->direction;
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

CharacterState * RyuKenStateFJump::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame(character->position, direction);

	character->nextPosition.y -= jumpSpeed;
	jumpSpeed += character->gravity;

	switch (direction)
	{
	case Direction::LEFT:
		character->nextPosition.x = character->position.x - (character->fJumpHSpeed * servicesManager->time->frameTimeSeconds);
		break;
	case Direction::RIGHT:
		character->nextPosition.x = character->position.x + (character->fJumpHSpeed * servicesManager->time->frameTimeSeconds);
	}

	if (character->nextPosition.y > character->groundLevel)
	{
		character->nextPosition.y = (float)character->groundLevel;
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}

void RyuKenStateFJump::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	switch (direction)
	{
	case Direction::LEFT:
		character->nextPosition.x = character->position.x - (character->pSpeed * servicesManager->time->frameTimeSeconds);
		break;
	case Direction::RIGHT:
		character->nextPosition.x = character->position.x + (character->pSpeed * servicesManager->time->frameTimeSeconds);
	}
}
