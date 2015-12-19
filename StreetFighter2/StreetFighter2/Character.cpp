#include "Character.h"
#include "Defines.h"
#include "config.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ParticleFactory.h"
#include "State.h"
#include "CharacterStateIdle.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "CommandState.h"

#include "ServiceCommandManager.h"

bool Character::Init()
{
	roundVictories = 0;
	life = 100;
	direction = Direction::RIGHT;

	speed = config->LoadIntValue(configSection, "speed", "0");;
	bSpeed = config->LoadIntValue(configSection, "bSpeed", "0");;
	fJumpDistance = config->LoadIntValue(configSection, "fJumpDistance", "0");;
	bJumpDistance = config->LoadIntValue(configSection, "bJumpDistance", "0");;

	config->LoadAnimation(idle, configSection, "idle");
	config->LoadAnimation(fWalk, configSection, "fWalk");
	config->LoadAnimation(bWalk, configSection, "bWalk");
	config->LoadAnimation(jump, configSection, "jump");
	config->LoadAnimation(fJump, configSection, "fJump");
	config->LoadAnimation(bJump, configSection, "bJump");
	config->LoadAnimation(crouch, configSection, "crouch");
	config->LoadAnimation(blocking, configSection, "blocking");
	config->LoadAnimation(cBlocking, configSection, "cBlocking");

	currentAnimation = &idle;
	currentState = new CharacterStateIdle(this);

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
	/*for (const auto& command : commandData->actions)
	{
		if (command == CommandAction::P1_L_KICK)
		{
			ParticleInfo pInfo;
			pInfo.type = ParticleInfo::Type::LOW_HADOKEN;
			pInfo.position.x = position.x;
			pInfo.position.y = position.y;
			pInfo.direction = direction;
			servicesManager->particles->CreateParticle(pInfo);
		}
	}

	for (const auto& command : commandData->states)
	{
		if (command == CommandState::P1_JUMP)
		{
			ParticleInfo pInfo;
			pInfo.type = ParticleInfo::Type::LOW_HADOKEN;
			pInfo.position.x = position.x;
			pInfo.position.y = position.y;
			pInfo.direction = direction;
			servicesManager->particles->CreateParticle(pInfo);
		}
	}

	//Debug
	currentAnimation = &idle;

	if (servicesManager->commands->P1UpLeft())
		currentAnimation = &bJump;
	else if (servicesManager->commands->P1UpRight())
		currentAnimation = &fJump;
	else if (servicesManager->commands->P1DownLeft())
		currentAnimation = &cBlocking;

	else if (servicesManager->commands->P1Right())
		currentAnimation = &bWalk;
	else if (servicesManager->commands->P1Down())
		currentAnimation = &crouch;
	else if (servicesManager->commands->P1Left())
		currentAnimation = &fWalk;
	else if (servicesManager->commands->P1Up())
		currentAnimation = &jump;
	
	//if (game->sCommands->P1Down)
	//	currentAnimation = &blocking;

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

Entity::Result Character::Draw()
{
	servicesManager->render->Blit(texture, currentAnimation->GetFrame().GetBlitPosition(position, direction), &(currentAnimation->GetFrame().rect), 1.0f, direction);
	return Entity::Result::R_OK;
}
