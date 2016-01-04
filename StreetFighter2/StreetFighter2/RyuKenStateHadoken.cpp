#include "RyuKenStateHadoken.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "ServicesManager.h"
#include "ServiceParticles.h"
#include "ParticleInfo.h"


RyuKenStateHadoken::RyuKenStateHadoken(RyuKen* p, AttackStrength s) : RyuKenState{ p }, strength{ s }, timer {1000}
{
}


RyuKenStateHadoken::~RyuKenStateHadoken()
{
}

void RyuKenStateHadoken::OnEnter()
{
	step = 0;
	character->currentAnimation = &character->hadoken;
	character->isAttacking = true;
	switch (strength)
	{
	case AttackStrength::LIGHT:
		character->PlaySfx(character->lHadokenSfx);
		break;
	case AttackStrength::MEDIUM:
		character->PlaySfx(character->mHadokenSfx);
		break;
	case AttackStrength::HARD:
		character->PlaySfx(character->hHadokenSfx);
		break;
	default:
		break;
	}

	RyuKenState::OnEnter();
}

void RyuKenStateHadoken::OnExit()
{
	RyuKenState::OnExit();
	character->ClearActionsSequence();
	character->isAttacking = false;
}

CharacterState * RyuKenStateHadoken::UpdateState()
{
	RyuKenState::UpdateState();

	switch (step)
	{
	case 0:
		if (character->currentAnimation->HasFinished())
		{
			ParticleInfo pInfo;
			pInfo.position.y = character->position.y + character->hadokenOffset.y;
			pInfo.position.x = character->position.x;
			switch (character->direction)
			{
			case Direction::LEFT:
				pInfo.position.x -= character->hadokenOffset.x;
				break;
			case Direction::RIGHT:
				pInfo.position.x += character->hadokenOffset.x;
			default:
				break;
			}

			pInfo.direction = character->direction;

			switch (strength)
			{
			case AttackStrength::LIGHT:
				pInfo.type = ParticleType::LIGHT_HADOKEN;
				break;
			case AttackStrength::MEDIUM:
				pInfo.type = ParticleType::MEDIUM_HADOKEN;
				break;
			case AttackStrength::HARD:
				pInfo.type = ParticleType::HARD_HADOKEN;
				break;
			default:
				break;
			}

			character->currentHadoken = servicesManager->particles->CreateParticle(pInfo);

			timer.Reset();
			++step;
		}
		break;

	case 1:
		if (timer.Reached())
		{
			return new RyuKenStateIdle(character);
		}
	default:
		break;
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	return nullptr;
}


