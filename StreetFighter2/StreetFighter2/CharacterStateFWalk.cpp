#include "CharacterStateFWalk.h"
#include "Character.h"


CharacterStateFWalk::CharacterStateFWalk(Character* p) : CharacterState(p)
{
}


CharacterStateFWalk::~CharacterStateFWalk()
{
}

void CharacterStateFWalk::OnEnter()
{
	character->currentAnimation = &character->fWalk;
	character->currentAnimation->ResetAnimation();
}
