#include "CharacterStateIdle.h"
#include "Character.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "CommandState.h"
#include "CharacterStateJump.h"


CharacterStateIdle::CharacterStateIdle(Character* p): CharacterState(p)
{
}


CharacterStateIdle::~CharacterStateIdle()
{
}

void CharacterStateIdle::OnEnter()
{
	//character->currentAnimation = &character->idle;
	//character->currentAnimation->ResetAnimation();
}

State * CharacterStateIdle::ProcessInput(CommandData * commandData)
{
	for (const auto& command : commandData->states)
	{
		if (character->playerNumber == 1)
		{
			switch (command)
			{
			//case Com
			case CommandState::P1_JUMP:
				return new CharacterStateJump(character);
				break;
			}
		}
		else
		{
			switch (command)
			{
			case CommandState::P2_JUMP:
				return new CharacterStateJump(character);
				break;
			}
		}
	}
	return nullptr;
}
