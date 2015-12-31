#include "RyuKenStateFWalk.h"
#include "RyuKen.h"
#include "ServicesManager.h"
#include "ServiceTime.h"
#include "RyuKenStateIdle.h"

RyuKenStateFWalk::RyuKenStateFWalk(RyuKen* p) : RyuKenState{ p }
{
}


RyuKenStateFWalk::~RyuKenStateFWalk()
{
}

void RyuKenStateFWalk::OnEnter()
{
	character->currentAnimation = &character->fWalk;
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
}

void RyuKenStateFWalk::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}


CharacterState * RyuKenStateFWalk::ProcessActions(std::vector<CommandAction> actions)
{
	return nullptr;
}

CharacterState * RyuKenStateFWalk::ProcessStates(std::vector<CommandState> states)
{
	bool keepWalking = false;

	for (const auto& command : states)
	{
		switch (command)
		{
		case CommandState::MOVE_LEFT:
			if (character->direction == Direction::LEFT)
				keepWalking = true;
			break;

		case CommandState::MOVE_RIGHT:
			if (character->direction == Direction::RIGHT)
				keepWalking = true;
			break;
		}
	}

	if (!keepWalking)
	{
		return new RyuKenStateIdle(character);
	}
	return nullptr;
}


CharacterState* RyuKenStateFWalk::UpdateState()
{
	switch (character->direction)
	{
	case Direction::LEFT:
		character->nextPosition.x = character->position.x - ((character->fSpeed) * (servicesManager->time->frameTimeSeconds));
		break;
	case Direction::RIGHT:
		character->nextPosition.x = character->position.x + ((character->fSpeed) * (servicesManager->time->frameTimeSeconds));
	}
	
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);	
	return nullptr;
}

void RyuKenStateFWalk::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	switch (character->direction)
	{
	case Direction::LEFT:
		character->nextPosition.x = character->position.x - ((character->pSpeed) * (servicesManager->time->frameTimeSeconds));
		break;
	case Direction::RIGHT:
		character->nextPosition.x = character->position.x + ((character->pSpeed) * (servicesManager->time->frameTimeSeconds));
	}
}
