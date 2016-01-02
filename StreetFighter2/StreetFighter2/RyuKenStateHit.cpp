#include "RyuKenStateHit.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"

RyuKenStateHit::RyuKenStateHit(RyuKen * p, bool crouch, bool face, float duration) : RyuKenState{ p }, crouching{ crouch }, faceHit { face }, hitDuration{ duration }
{
}

RyuKenStateHit::~RyuKenStateHit()
{
}

void RyuKenStateHit::OnEnter()
{
	character->ClearActionsSequence();

	if (crouching)
	{
		character->currentAnimation = &character->cHit;
	}
	else
	{
		if (faceHit)
			character->currentAnimation = &character->faceHit;
		else
			character->currentAnimation = &character->hit;
	}

	character->currentAnimation->SetDuration(hitDuration);
	RyuKenState::OnEnter();
}

CharacterState* RyuKenStateHit::UpdateState()
{
	RyuKenState::UpdateState();

	if(character->hitBackwardMovement == 0.0f)
		return new RyuKenStateIdle(character);

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}

