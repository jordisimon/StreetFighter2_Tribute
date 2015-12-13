#include "Player.h"
#include "Defines.h"
#include "Game.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ParticleFactory.h"
#include "State.h"
#include "PlayerStateIdle.h"

#include "ServiceCommandManager.h"

bool Player::Init(const Config & config)
{
	life = 100;
	direction = Direction::RIGHT;

	speed = config.LoadIntValue(configSection, "speed", "0");;
	bSpeed = config.LoadIntValue(configSection, "bSpeed", "0");;
	fJumpDistance = config.LoadIntValue(configSection, "fJumpDistance", "0");;
	bJumpDistance = config.LoadIntValue(configSection, "bJumpDistance", "0");;

	config.LoadAnimation(idle, configSection, "idle");
	config.LoadAnimation(fWalk, configSection, "fWalk");
	config.LoadAnimation(bWalk, configSection, "bWalk");
	config.LoadAnimation(jump, configSection, "jump");
	config.LoadAnimation(fJump, configSection, "fJump");
	config.LoadAnimation(bJump, configSection, "bJump");
	config.LoadAnimation(crouch, configSection, "crouch");
	config.LoadAnimation(blocking, configSection, "blocking");
	config.LoadAnimation(cBlocking, configSection, "cBlocking");

	currentAnimation = &idle;
	currentState = new PlayerStateIdle(this);

	return true;
}

bool Player::Start()
{
	LOG("Starting player");

	texture = game->sTextures->Load(configSection);

	return true;
}

bool Player::Stop()
{
	LOG("Stopping player");

	game->sTextures->Unload(texture);

	return true;
}

Entity::Result Player::ProcessInput()
{
	//Debug
	currentAnimation = &idle;

	if (game->sCommands->P1UpLeft())
		currentAnimation = &bJump;
	else if (game->sCommands->P1UpRight())
		currentAnimation = &fJump;
	else if (game->sCommands->P1DownLeft())
		currentAnimation = &cBlocking;

	else if (game->sCommands->P1Right())
		currentAnimation = &bWalk;
	else if (game->sCommands->P1Down())
		currentAnimation = &crouch;
	else if (game->sCommands->P1Left())
		currentAnimation = &fWalk;
	else if (game->sCommands->P1Up())
		currentAnimation = &jump;
	
	//if (game->sCommands->P1Down)
	//	currentAnimation = &blocking;

	if (game->sCommands->P1LPunch())
	{
		ParticleInfo pInfo;
		pInfo.type = ParticleInfo::Type::LOW_HADOKEN;
		pInfo.position.x = position.x;
		pInfo.position.y = position.y;
		pInfo.direction = direction;
		game->sParticles->CreateParticle(pInfo);
	}

	State* newState = currentState->ProcessInput();
	if (newState != nullptr)
	{
		currentState->OnExit();
		RELEASE(currentState);
		currentState = newState;
		newState->OnEnter();
	}

	return Entity::Result::R_OK;
}

Entity::Result Player::UpdateState()
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

Entity::Result Player::Draw()
{
	game->sRender->Blit(texture, currentAnimation->GetFrame().GetBlitPosition(position, direction), &(currentAnimation->GetFrame().rect), 0.87f, direction);
	return Entity::Result::R_OK;
}
