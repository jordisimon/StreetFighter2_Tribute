#include "CharacterStateJump.h"
#include "Character.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "CommandState.h"


CharacterStateJump::CharacterStateJump(Character* p) : CharacterState(p)
{
}


CharacterStateJump::~CharacterStateJump()
{
}

void CharacterStateJump::OnEnter()
{
	//character->currentAnimation = &character->jump;
	//character->currentAnimation->ResetAnimation();
}

State * CharacterStateJump::ProcessInput(CommandData * commandData)
{
	return nullptr;
}
