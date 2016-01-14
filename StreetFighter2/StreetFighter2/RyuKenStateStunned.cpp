#include "RyuKenStateStunned.h"
#include "RyuKen.h"
#include "ServicesManager.h"
#include "ServiceParticles.h"
#include "Particle.h"
#include "ParticleInfo.h"
#include "RyuKenStateIdle.h"

RyuKenStateStunned::RyuKenStateStunned(RyuKen* p, bool st) : RyuKenState{ p, false }, strong{ st }, canReduceTime { true }
{
}


RyuKenStateStunned::~RyuKenStateStunned()
{
}

void RyuKenStateStunned::OnEnter()
{
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

	if (character->particleStunned != nullptr)
	{
		character->particleStunned->toDelete;
		character->particleStunned = nullptr;
	}

	character->particleStunned = servicesManager->particles->CreateParticle(info);

	character->SetCurrentAnimation(character->stunned);
}

void RyuKenStateStunned::OnExit()
{
	RyuKenState::OnExit();

	character->particleStunned->toDelete = true;
	character->particleStunned = nullptr;
}

CharacterState * RyuKenStateStunned::ProcessActions(std::vector<CommandAction> actions)
{
	for (auto const& command : actions)
	{
		//Only one reduction per tick
		if (canReduceTime)
		{
			switch (command)
			{
			case CommandAction::MOVE_UP:
			case CommandAction::MOVE_DOWN:
			case CommandAction::MOVE_LEFT:
			case CommandAction::MOVE_RIGHT:
			case CommandAction::MOVE_UP_LEFT:
			case CommandAction::MOVE_UP_RIGHT:
			case CommandAction::MOVE_DOWN_LEFT:
			case CommandAction::MOVE_DOWN_RIGHT:
			case CommandAction::L_PUNCH:
			case CommandAction::M_PUNCH:
			case CommandAction::H_PUNCH:
			case CommandAction::L_KICK:
			case CommandAction::M_KICK:
			case CommandAction::H_KICK:
				character->stunnedTimer.AddElapsedTime(100);
				canReduceTime = false;
				break;
			default:
				break;
			}
		}
	}

	return nullptr;
}

CharacterState * RyuKenStateStunned::UpdateState()
{
	RyuKenState::UpdateState();

	canReduceTime = true;
	character->ClearActionsSequence();
	character->knockdownDamage = 0;

	if (character->stunnedTimer.Reached())
	{
		return new RyuKenStateIdle(character);
	}

	return nullptr;
}
