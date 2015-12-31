#include "RyuKenStateBWalk.h"
#include "RyuKen.h"
#include "ServicesManager.h"
#include "ServiceTime.h"
#include "RyuKenStateIdle.h"
#include "SceneMatch.h"

RyuKenStateBWalk::RyuKenStateBWalk(RyuKen* p) : RyuKenState{ p }
{
}


RyuKenStateBWalk::~RyuKenStateBWalk()
{
}

void RyuKenStateBWalk::OnEnter()
{
	character->currentAnimation = &character->bWalk;
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
}

void RyuKenStateBWalk::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}


CharacterState * RyuKenStateBWalk::ProcessActions(std::vector<CommandAction> actions)
{
	return nullptr;
}

CharacterState * RyuKenStateBWalk::ProcessStates(std::vector<CommandState> states)
{
	bool keepWalking = false;

	for (const auto& command : states)
	{
		switch (command)
		{
		case CommandState::MOVE_LEFT:
			if (character->direction == Direction::RIGHT)
				keepWalking = true;
			break;

		case CommandState::MOVE_RIGHT:
			if (character->direction == Direction::LEFT)
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

CharacterState* RyuKenStateBWalk::UpdateState()
{
	switch (character->direction)
	{
	case Direction::LEFT:
		character->nextPosition.x = character->position.x + ((character->bSpeed) * (servicesManager->time->frameTimeSeconds));
		break;
	case Direction::RIGHT:
		character->nextPosition.x = character->position.x - ((character->bSpeed) * (servicesManager->time->frameTimeSeconds));
		break;
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}
