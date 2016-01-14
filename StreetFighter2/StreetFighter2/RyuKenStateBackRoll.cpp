#include "RyuKenStateBackRoll.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"


RyuKenStateBackRoll::RyuKenStateBackRoll(RyuKen* p, Direction dir) : RyuKenState{ p, false }, direction{ dir }, step{ 0 }, state{ BackRollState::GRABBING }
{
}


RyuKenStateBackRoll::~RyuKenStateBackRoll()
{
}

void RyuKenStateBackRoll::OnEnter()
{
	character->rival->position = character->position;
	character->rival->Grabbed();
	character->rival->SetCurrentAnimation(character->rival->grabbed);
	
	character->SetCurrentAnimation(character->backRoll);
	character->PlaySfx(character->grabSfx);
}

CharacterState * RyuKenStateBackRoll::UpdateState()
{
	RyuKenState::UpdateState();

	character->rival->UpdateCurrentAnimation();

	switch (state)
	{
	case RyuKenStateBackRoll::BackRollState::GRABBING:
		//Only once per animation frame
		if (step == character->currentAnimation->GetCurrentFrameIndex())
		{
			float deltaX = 0.0f;
			float deltaY = 0.0f;

			switch (step)
			{
			case 0:
				deltaX = -12;
				break;
			case 1:
				//deltaX = -10;
				deltaY = -10;
				break;
			case 2:
				deltaX = 30;
				deltaY = -23;
				break;
			case 3:
				deltaX = 25;
				deltaY = -4;
				break;
			case 4:
				deltaX = 30;
				deltaY = -5;
				character->rival->isGrabbed = false;
				break;
			default:
				break;
			}

			if (direction == Direction::LEFT)
				deltaX *= -1;

			character->rival->nextPosition.x = character->rival->position.x + deltaX;
			character->rival->nextPosition.y = character->rival->position.y + deltaY;

			++step;
		}

		if (character->currentAnimation->HasFinished())
		{
			character->rival->SubstractDamage(27);
			character->rival->Thrown();

			state = BackRollState::WAITING;
			timer.Resume();
			timer.SetNewInterval(750);		
		}

		break;

	case RyuKenStateBackRoll::BackRollState::WAITING:
		if (timer.Reached())
		{
			state = BackRollState::RECOVERING;
			character->SetCurrentAnimation(character->backRollRecover);
		}		
		break;

	case RyuKenStateBackRoll::BackRollState::RECOVERING:
		if (character->currentAnimation->HasFinished())
		{
			return new RyuKenStateIdle(character);
		}
		break;
	default:
		break;
	}

	return nullptr;
}
