#include "RyuKenStateHit.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"

RyuKenStateHit::RyuKenStateHit(RyuKen * p, bool face, float duration) : RyuKenState{ p }, faceHit{face}, hitDuration{duration}
{
}

RyuKenStateHit::~RyuKenStateHit()
{
}

void RyuKenStateHit::OnEnter()
{
	if(faceHit)
		character->currentAnimation = &character->faceHit;
	else
		character->currentAnimation = &character->hit;


	character->currentAnimation->SetDuration(hitDuration);
	character->currentAnimation->ResetAnimation();
	character->currentAnimation->InitColliders(character->position, character->direction);
}

void RyuKenStateHit::OnExit()
{
	character->currentAnimation->CleanUpColliders();
}

CharacterState* RyuKenStateHit::UpdateState()
{
	if (character->currentAnimation->HasFinished())
		return new RyuKenStateIdle(character);

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}

