#include "RyuKenStateStunned.h"
#include "RyuKen.h"
#include "Particle.h"
#include "RyuKenStateIdle.h"

RyuKenStateStunned::RyuKenStateStunned(RyuKen* p) : RyuKenState{ p }, canReduceTime{ true }
{
}


RyuKenStateStunned::~RyuKenStateStunned()
{
}

void RyuKenStateStunned::OnEnter()
{
	character->currentAnimation = &character->stunned;

	RyuKenState::OnEnter();
}

void RyuKenStateStunned::OnExit()
{
	RyuKenState::OnExit();
}

CharacterState * RyuKenStateStunned::ProcessActions(std::vector<CommandAction> actions)
{
	for (auto const& command : actions)
	{
		//Only one reduction per tick
		if (canReduceTime)
		{
			switch (command)
			{
			case CommandAction::MOVE_UP:
			case CommandAction::MOVE_DOWN:
			case CommandAction::MOVE_LEFT:
			case CommandAction::MOVE_RIGHT:
			case CommandAction::MOVE_UP_LEFT:
			case CommandAction::MOVE_UP_RIGHT:
			case CommandAction::MOVE_DOWN_LEFT:
			case CommandAction::MOVE_DOWN_RIGHT:
			case CommandAction::L_PUNCH:
			case CommandAction::M_PUNCH:
			case CommandAction::H_PUNCH:
			case CommandAction::L_KICK:
			case CommandAction::M_KICK:
			case CommandAction::H_KICK:
				character->stunnedTimer.AddElapsedTime(100);
				canReduceTime = false;
				break;
			default:
				break;
			}
		}
	}

	return nullptr;
}

CharacterState * RyuKenStateStunned::UpdateState()
{
	RyuKenState::UpdateState();

	canReduceTime = true;
	character->ClearActionsSequence();
	character->knockdownDamage = 0;
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	if (character->stunnedTimer.Reached())
	{
		character->isStunned = false;
		character->particleStunned->toDelete = true;
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}
