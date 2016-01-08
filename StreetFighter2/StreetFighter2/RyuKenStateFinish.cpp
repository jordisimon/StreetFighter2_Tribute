#include "RyuKenStateFinish.h"
#include "RyuKen.h"
#include "Particle.h"
#include <time.h>   


RyuKenStateFinish::RyuKenStateFinish(RyuKen* p, int pWin) : RyuKenState{ p }, playerWin{ pWin }, falling{ false }
{
}


RyuKenStateFinish::~RyuKenStateFinish()
{
}

void RyuKenStateFinish::OnEnter()
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
		character->yUpdateControl = 1.0f; // to force not being in ground when updating first time
		character->currentAnimation = &character->KOBegin;
		character->PlaySfx(character->KOSfx);
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

CharacterState * RyuKenStateFinish::UpdateState()
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
				character->PlaySfx(character->floorHitSfx);
			}

			falling = false;
		}
	}
	else
	{
		character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	}

	return nullptr;
}
