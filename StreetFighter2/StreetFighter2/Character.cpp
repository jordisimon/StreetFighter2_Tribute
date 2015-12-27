#include "Character.h"
#include "Defines.h"
#include "config.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"
#include "ParticleFactory.h"
#include "State.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "CommandState.h"
#include "ColliderType.h"

#include "ServiceCommandManager.h"

bool Character::Init()
{
	roundVictories = 0;
	life = 100;
	direction = Direction::RIGHT;

	characterId = config->LoadIntValue(configSection, "characterId", "-1");
	fSpeed = config->LoadIntValue(configSection, "fSpeed", "0");
	bSpeed = config->LoadIntValue(configSection, "bSpeed", "0");
	jumpVSpeed = config->LoadFloatValue(configSection, "jumpVSpeed", "0");
	fJumpHSpeed = config->LoadIntValue(configSection, "fJumpHSpeed", "0");
	bJumpHSpeed = config->LoadIntValue(configSection, "bJumpHSpeed", "0");
	gravity = config->LoadFloatValue("Physics", "gravity", "-2");
	margin = config->LoadFloatValue(configSection, "margin", "0");

	return true;
}

bool Character::Start()
{
	LOG("Starting player");

	texture = servicesManager->textures->Load(configSection);

	return true;
}

bool Character::Stop()
{
	LOG("Stopping player");

	servicesManager->textures->Unload(texture);

	return true;
}

bool Character::ProcessInput(CommandData* commandData)
{
	/*
	if (servicesManager->commands->P1LPunch())
	{
		ParticleInfo pInfo;
		pInfo.type = ParticleInfo::Type::LOW_HADOKEN;
		pInfo.position.x = position.x;
		pInfo.position.y = position.y;
		pInfo.direction = direction;
		servicesManager->particles->CreateParticle(pInfo);
	}*/

	State* newState = currentState->ProcessInput(commandData);
	if (newState != nullptr)
	{
		currentState->OnExit();
		RELEASE(currentState);
		currentState = newState;
		newState->OnEnter();
	}

	return true;
}

Entity::Result Character::UpdateState()
{
	State* newState = currentState->UpdateState();

	if (newState != nullptr)
	{
		currentState->OnExit();
		RELEASE(currentState);
		currentState = newState;
		newState->OnEnter();
	}

	return Entity::Result::R_OK;
}

/*Entity::Result Character::Draw()
{
	servicesManager->render->Blit(texture, currentAnimation->GetFrame().GetBlitPosition(position, direction), &(currentAnimation->GetFrame().rect), 1.0f, direction);

	return Entity::Result::R_OK;
}*/
