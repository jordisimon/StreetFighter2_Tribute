#include "RyuKenStateShoulderToss.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"


RyuKenStateShoulderToss::RyuKenStateShoulderToss(RyuKen* p, Direction dir) : RyuKenState{ p }, direction{ dir }, step{ 0 }
{
}


RyuKenStateShoulderToss::~RyuKenStateShoulderToss()
{
}

void RyuKenStateShoulderToss::OnEnter()
{
	character->rival->Grabbed();
	character->rival->currentAnimation = &character->rival->grabbed;
	character->rival->currentAnimation->ResetAnimation();
	character->rival->position = character->position;

	character->currentAnimation = &character->shoulderToss;

	character->PlaySfx(character->grabSfx);

	RyuKenState::OnEnter();
}

CharacterState * RyuKenStateShoulderToss::UpdateState()
{
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
		return new RyuKenStateIdle(character);
	}


	character->rival->currentAnimation->UpdateCurrentFrame(character->rival->position, character->rival->direction);
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	return nullptr;
}

void RyuKenStateShoulderToss::Draw() const
{
	character->DrawDefault(direction);
}
