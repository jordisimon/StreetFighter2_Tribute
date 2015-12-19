#include "CharacterState.h"
#include "Character.h"

CharacterState::CharacterState(Character* p) : character{ p }
{
}


CharacterState::~CharacterState()
{
}

State * CharacterState::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame();
	return nullptr;
}
