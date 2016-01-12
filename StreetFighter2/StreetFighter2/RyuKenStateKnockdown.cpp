#include "RyuKenStateKnockdown.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateStunned.h"


RyuKenStateKnockdown::RyuKenStateKnockdown(RyuKen* p, Direction animDir) : RyuKenState{ p }, animDirection{ animDir }, step { 0 }
{
}


RyuKenStateKnockdown::~RyuKenStateKnockdown()
{
}

void RyuKenStateKnockdown::OnEnter()
{
	character->currentAnimation = &character->knockdown;

	character->hitBackwardMovement = 100.0f;
	character->hitBackwardSpeed = 120.0f;
	character->currentJumpSpeed = 5.5f;
	character->applyBackwardMovementToOtherPlayerRatio = 0.25f;
	character->knockdownTimer.Pause();

	RyuKenState::OnEnter();
}

void RyuKenStateKnockdown::OnExit()
{
	RyuKenState::OnExit();
	
	character->knockdownDamage = 0;
	character->knockdownTimer.Resume();
}


CharacterState * RyuKenStateKnockdown::UpdateState()
{
	RyuKenState::UpdateState();

	character->ClearActionsSequence();

	switch (step)
	{
	case 0:
		if (character->nextPosition.y >= character->groundLevel)
		{
			RyuKenState::OnExit();
			character->currentAnimation = &character->knockdownRecover;
			RyuKenState::OnEnter();
			character->PlaySfx(character->floorHitSfx);
			++step;
		}
		break;

	case 1:
		if (character->currentAnimation->HasFinished())
		{
			if (character->knockdownDamage < 50)
			{
				return new RyuKenStateIdle(character);
			}
			else
			{
				if (character->knockdownDamage <= 65)
					return new RyuKenStateStunned(character, false);
				else
					return new RyuKenStateStunned(character, true);
			}
		}
		break;

	default:
		break;
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, animDirection);

	return nullptr;
}

void RyuKenStateKnockdown::Draw() const
{
	character->DrawDefault(animDirection);
}
