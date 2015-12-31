#include "RyuKenState.h"
#include "RyuKen.h"
#include "CommandData.h"
#include "RyuKenStateHit.h"
#include "RyuKenFinishState.h"
#include "Collider.h"
#include "ColliderType.h"
#include "ServicesManager.h"
#include "ServiceParticles.h"
#include "ParticleInfo.h"


RyuKenState::RyuKenState(RyuKen* p) : character{ p }
{
}


RyuKenState::~RyuKenState()
{
}

CharacterState * RyuKenState::ProcessInput(CommandData * commandData)
{
	//Default behaviour
	CharacterState* result = nullptr;

	if (character->playerNumber == 1)
	{
		result = ProcessActions(commandData->p1Actions);
		if (result == nullptr)
			result = ProcessStates(commandData->p1States);
	}
	else
	{
		result = ProcessActions(commandData->p2Actions);
		if (result == nullptr)
			result = ProcessStates(commandData->p2States);
	}

	return result;
}

CharacterState * RyuKenState::DealHit(Collider * collider)
{
	//Needed info
	//int damage;

	bool faceHit = true;

	 

	if (collider->type == ColliderType::CHARACTER_ATTACK)
	{
		Character* enemy = (Character*)collider->listener;
		character->life -= enemy->currentAttackDamage;
		if (character->life < 0)
			character->life = 0;
		character->applyToOtherPlayer = true;
	}
	else if (collider->type == ColliderType::ATTACK_PARTICLE)
	{
		faceHit = true;
		character->applyToOtherPlayer = false;
	}

	ParticleInfo info;
	info.type = ParticleType::P1_HHIT;
	info.direction = character->direction;
	info.position.x = collider->colliderRect.x;
	info.position.y = collider->colliderRect.y;

	servicesManager->particles->CreateParticle(info);

	//return nullptr;
	character->hitBackwardMovement = 50.0f;
	character->hitBackwardSpeed = 40.0f;


	return new RyuKenStateHit(character, faceHit, 0.5f);
}

CharacterState * RyuKenState::MatchFinished(int playerWin)
{
	return new RyuKenFinishState(character, playerWin);
}
