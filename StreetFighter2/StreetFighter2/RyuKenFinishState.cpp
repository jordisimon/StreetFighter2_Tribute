#include "RyuKenFinishState.h"
#include "RyuKen.h"
#include <time.h>   



RyuKenFinishState::RyuKenFinishState(RyuKen* p, int pWin) : RyuKenState{ p }, playerWin{ pWin }, falling{ false }
{
}


RyuKenFinishState::~RyuKenFinishState()
{
}

void RyuKenFinishState::OnEnter()
{
	if (character->position.y < character->groundLevel)
	{
		falling = true;
	}

	if (character->life == 0)
	{
		character->hitBackwardMovement = 100.0f;
		character->hitBackwardSpeed = 120.0f;
		character->currentJumpSpeed = 5.5f;
		character->applyToOtherPlayer = false;
		character->currentAnimation = &character->KOBegin;
		falling = true;
	}
	else
	{
		if (character->playerNumber == playerWin)
		{
			srand((unsigned int)time(NULL));
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
			character->currentAnimation = &character->timeover;
		}
	}

	RyuKenState::OnEnter();
}

CharacterState * RyuKenFinishState::UpdateState()
{
	RyuKenState::UpdateState();

	if (falling)
	{
		character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

		if (character->nextPosition.y >= character->groundLevel)
		{
			if (character->life > 0)
			{
				if (character->playerNumber == playerWin)
				{
					srand((unsigned int)time(NULL));
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
					character->currentAnimation = &character->timeover;
				}
			}
			else
			{
				character->currentAnimation = &character->KOEnd;
			}

			falling = false;
		}
		/*else
		{
			if (character->currentAnimation == &character->KOBegin)
			{
				if(character->direction == Direction::LEFT)
					character->MoveXPosition(Direction::RIGHT, character->bSpeed);
				else
					character->MoveXPosition(Direction::LEFT, character->bSpeed);
			}
		}*/
	}
	else
	{
		character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	}

	return nullptr;
}
