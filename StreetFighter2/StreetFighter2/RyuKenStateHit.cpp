#include "RyuKenStateHit.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateStunned.h"

RyuKenStateHit::RyuKenStateHit(RyuKen * p, bool crouch, bool face, AttackStrength str) 
	: RyuKenState{ p, false }, crouching{ crouch }, faceHit{ face }, strength{ str }
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
		character->SetCurrentAnimation(character->cHit);
	}
	else
	{
		if (faceHit)
			character->SetCurrentAnimation(character->faceHit);
		else
			character->SetCurrentAnimation(character->hit);
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
}

CharacterState* RyuKenStateHit::UpdateState()
{
	RyuKenState::UpdateState();

	if (character->hitBackwardMovement == 0.0f)
	{
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}

