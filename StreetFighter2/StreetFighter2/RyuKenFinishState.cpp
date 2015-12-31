#include "RyuKenFinishState.h"
#include "RyuKen.h"
#include <time.h>   



RyuKenFinishState::RyuKenFinishState(RyuKen* p, int pWin) : RyuKenState{ p }, playerWin{ pWin }
{
}


RyuKenFinishState::~RyuKenFinishState()
{
}

void RyuKenFinishState::OnEnter()
{

	if (character->playerNumber == playerWin)
	{
		srand(time(NULL));
		int random = rand() % 2;

		switch (random)
		{
		case 0:
			character->currentAnimation = &character->victory1;
			break;
		case 1:
			character->currentAnimation = &character->victory2;
			break;
		default:
			character->currentAnimation = &character->victory1;
			break;
		}
	}
	else
	{
		if (character->life > 0)
			character->currentAnimation = &character->timeover;
		else
		{
			character->hitBackwardMovement = 20.0f;
			character->hitBackwardSpeed = 20.0f;
			character->applyToOtherPlayer = false;
			character->currentAnimation = &character->KO;
		}
	}
}

CharacterState * RyuKenFinishState::UpdateState()
{
	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}
