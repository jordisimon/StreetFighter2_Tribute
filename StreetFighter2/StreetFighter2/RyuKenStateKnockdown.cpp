#include "RyuKenStateKnockdown.h"
#include "RyuKen.h"
#include "ServicesManager.h"
#include "ServiceParticles.h"
#include "Particle.h"
#include "ParticleInfo.h"
#include "RyuKenStateStunned.h"


RyuKenStateKnockdown::RyuKenStateKnockdown(RyuKen* p, bool s) : RyuKenState{ p }, strong{ s }, step{ 0 }
{
}


RyuKenStateKnockdown::~RyuKenStateKnockdown()
{
}

void RyuKenStateKnockdown::OnEnter()
{
	character->currentAnimation = &character->knockdown;

	character->hitBackwardMovement = 100.0f;
	character->hitBackwardSpeed = 120.0f;
	character->currentJumpSpeed = 5.5f;
	character->applyToOtherPlayer = false;

	RyuKenState::OnEnter();
}


CharacterState * RyuKenStateKnockdown::UpdateState()
{
	RyuKenState::UpdateState();

	character->ClearActionsSequence();
	character->knockdownDamage = 0;

	switch (step)
	{
	case 0:
		if (character->nextPosition.y >= character->groundLevel)
		{
			RyuKenState::OnExit();
			character->currentAnimation = &character->knockdownRecover;
			RyuKenState::OnEnter();
			character->PlaySfx(character->floorHitSfx);
			++step;
		}
		break;

	case 1:
		if (character->currentAnimation->HasFinished())
		{

			RyuKenState::OnExit();
			character->currentAnimation = &character->stunned;
			RyuKenState::OnEnter();

			ParticleInfo info;
			info.position.x = character->position.x;
			info.position.y = character->position.y - character->height - 30;
			info.direction = character->direction;

			if (strong)
			{
				info.type = ParticleType::STARS;
				character->stunnedTimer.SetNewInterval(3000);
			}
			else
			{
				info.type = ParticleType::DUCKS;
				character->stunnedTimer.SetNewInterval(5000);
			}

			character->isStunned = true;
			if (character->particleStunned != nullptr)
				character->particleStunned->toDelete;
			character->particleStunned = servicesManager->particles->CreateParticle(info);
			return new RyuKenStateStunned(character);
		}
		break;

	default:
		break;
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);

	return nullptr;
}
