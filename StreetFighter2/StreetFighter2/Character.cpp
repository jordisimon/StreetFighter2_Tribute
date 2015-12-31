#include "Character.h"
#include "Defines.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"
#include "ParticleFactory.h"
#include "CharacterState.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "CommandState.h"
#include "Collider.h"
#include "ColliderType.h"

#include "ServiceCommandManager.h"

bool Character::Init()
{
	LOG("Init player");
	texture = servicesManager->textures->Load(configSection);

	roundVictories = 0;
	direction = Direction::RIGHT;
	characterId = config->LoadIntValue(configSection, "characterId", "-1");
	fSpeed = config->LoadIntValue(configSection, "fSpeed", "0");
	bSpeed = config->LoadIntValue(configSection, "bSpeed", "0");
	pSpeed = config->LoadIntValue(configSection, "pSpeed", "0");
	jumpVSpeed = config->LoadFloatValue(configSection, "jumpVSpeed", "0");
	fJumpHSpeed = config->LoadIntValue(configSection, "fJumpHSpeed", "0");
	bJumpHSpeed = config->LoadIntValue(configSection, "bJumpHSpeed", "0");
	gravity = config->LoadFloatValue("Physics", "gravity", "-2");
	height = config->LoadFloatValue(configSection, "height", "0");
	fMargin = config->LoadFloatValue(configSection, "fMargin", "0");
	bMargin = config->LoadFloatValue(configSection, "bMargin", "0");

	config->LoadSprite(shadow, configSection, "shadow");

	return true;
}

bool Character::CleanUp()
{
	LOG("CleanUp player");

	servicesManager->textures->Unload(texture);

	return true;
}

bool Character::Start()
{
	life = 100;
	shownLife = 100.0f;
	currentAttackDamage = 0;
	hitBackwardMovement = 0.0f;
	hitBackwardSpeed = 0.0f;
	applyToOtherPlayer = false;

	return true;
}

bool Character::Stop()
{
	return true;
}

void Character::SetNewState(CharacterState * state)
{
	if (state != nullptr)
	{
		currentState->OnExit();
		RELEASE(currentState);
		currentState = state;
		currentState->OnEnter();
	}
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

	SetNewState(currentState->ProcessInput(commandData));

	return true;
}

Entity::Result Character::UpdateState()
{
	SetNewState(nextState);
	nextState = nullptr;
	SetNewState(currentState->UpdateState());

	return Entity::Result::R_OK;
}

void Character::OnCollitionEnter(Collider * colA, Collider * colB)
{
	if (colB->type == ColliderType::CHARACTER_ATTACK || colB->type == ColliderType::ATTACK_PARTICLE)
	{
		nextState = currentState->DealHit(colB);
	}
}

void Character::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	currentState->IfMovingForwardRecalculatePositionWithPressingSpeed();
}

void Character::DrawShadow(int groundLevel) const
{
	fPoint pos;
	pos.y = (float)groundLevel;
	pos.x = position.x;
	servicesManager->render->BlitScene(texture, shadow.GetRectPosition(pos, direction), shadow.rect, 1.0f, direction);
}

Entity::Result Character::Draw() const
{
	servicesManager->render->BlitScene(texture, currentAnimation->GetFrame().GetRectPosition(position, direction), currentAnimation->GetFrame().rect, 1.0f, direction);

	//TODO: Remove
	servicesManager->render->SetDrawColor(Color(Color::Predefined::MAGENTA));
	servicesManager->render->DrawRectFill({ position.x - 1, position.y - 1, 2, 2 });

	return Entity::Result::R_OK;
}
