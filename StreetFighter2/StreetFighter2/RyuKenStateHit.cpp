#include "RyuKenStateHit.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateStunned.h"

RyuKenStateHit::RyuKenStateHit(RyuKen * p, bool crouch, bool face, AttackStrength str) 
	: RyuKenState{ p }, crouching{ crouch }, faceHit{ face }, strength{ str }
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

	switch (strength)
	{
	case AttackStrength::LIGHT:
		character->currentAnimation->SetDuration(0.3f);
		break;

	case AttackStrength::MEDIUM:
		character->currentAnimation->SetDuration(0.6f);
		break;

	case AttackStrength::HARD:
		character->currentAnimation->SetDuration(0.9f);
		break;
	}

	RyuKenState::OnEnter();
}

CharacterState* RyuKenStateHit::UpdateState()
{
	RyuKenState::UpdateState();

	if (character->hitBackwardMovement == 0.0f)
	{
		return new RyuKenStateIdle(character);
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}

