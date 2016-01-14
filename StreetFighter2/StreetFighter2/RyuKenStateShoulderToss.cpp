#include "RyuKenStateShoulderToss.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"


RyuKenStateShoulderToss::RyuKenStateShoulderToss(RyuKen* p, Direction dir) : RyuKenState{ p, false }, direction{ dir }, step{ 0 }, state{ ShoulderTossState::GRABBING }
{
}


RyuKenStateShoulderToss::~RyuKenStateShoulderToss()
{
}

void RyuKenStateShoulderToss::OnEnter()
{
	character->rival->position = character->position;
	character->rival->Grabbed();
	character->rival->SetCurrentAnimation(character->rival->grabbed);

	character->SetCurrentAnimation(character->shoulderToss);
	character->PlaySfx(character->grabSfx);
}

CharacterState * RyuKenStateShoulderToss::UpdateState()
{
	RyuKenState::UpdateState();

	character->rival->UpdateCurrentAnimation();

	switch (state)
	{
	case ShoulderTossState::GRABBING:
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
				deltaX = -10;
				deltaY = -20;
				break;
			case 2:
				deltaX = 12;
				deltaY = -30;
				break;
			case 3:
				deltaX = 20;
				deltaY = -5;
				character->rival->isGrabbed = false;
				break;
			case 4:
				deltaX = 30;
				deltaY = -5;
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

			state = ShoulderTossState::WAITING;
			timer.Resume();
			timer.SetNewInterval(1000);	
		}
		break;

	case ShoulderTossState::WAITING:
		if(timer.Reached())
			return new RyuKenStateIdle(character);
		break;

	default:
		break;
	}

	return nullptr;
}
