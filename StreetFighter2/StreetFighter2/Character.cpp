#include "Character.h"
#include "Defines.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"
#include "ServiceTime.h"
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

void Character::StoreActions(std::vector<CommandAction> actions)
{
	for (const auto& command : actions)
	{
		switch (command)
		{
		case CommandAction::MOVE_UP:
			actionsSequence.emplace_front(SpecialAction::UP);
			break;
		case CommandAction::MOVE_DOWN:
			actionsSequence.emplace_front(SpecialAction::DOWN);
			break;
		case CommandAction::MOVE_LEFT:
			if(direction == Direction::LEFT)
				actionsSequence.emplace_front(SpecialAction::FORWARD);
			else
				actionsSequence.emplace_front(SpecialAction::BACKWARD);
			break;
		case CommandAction::MOVE_RIGHT:
			if (direction == Direction::RIGHT)
				actionsSequence.emplace_front(SpecialAction::FORWARD);
			else
				actionsSequence.emplace_front(SpecialAction::BACKWARD);
			break;
		case CommandAction::MOVE_UP_LEFT:
			if (direction == Direction::LEFT)
				actionsSequence.emplace_front(SpecialAction::UP_FORWARD);
			else
				actionsSequence.emplace_front(SpecialAction::UP_BACKWARD);
			break;
		case CommandAction::MOVE_UP_RIGHT:
			if (direction == Direction::RIGHT)
				actionsSequence.emplace_front(SpecialAction::UP_FORWARD);
			else
				actionsSequence.emplace_front(SpecialAction::UP_BACKWARD);
			break;
		case CommandAction::MOVE_DOWN_LEFT:
			if (direction == Direction::LEFT)
				actionsSequence.emplace_front(SpecialAction::DOWN_FORWARD);
			else
				actionsSequence.emplace_front(SpecialAction::DOWN_BACKWARD);
			break;
		case CommandAction::MOVE_DOWN_RIGHT:
			if (direction == Direction::RIGHT)
				actionsSequence.emplace_front(SpecialAction::DOWN_FORWARD);
			else
				actionsSequence.emplace_front(SpecialAction::DOWN_BACKWARD);
			break;
		case CommandAction::L_PUNCH:
			actionsSequence.emplace_front(SpecialAction::L_PUNCH);
			break;
		case CommandAction::M_PUNCH:
			actionsSequence.emplace_front(SpecialAction::M_PUNCH);
			break;
		case CommandAction::H_PUNCH:
			actionsSequence.emplace_front(SpecialAction::H_PUNCH);
			break;
		case CommandAction::L_KICK:
			actionsSequence.emplace_front(SpecialAction::L_KICK);
			break;
		case CommandAction::M_KICK:
			actionsSequence.emplace_front(SpecialAction::M_KICK);
			break;
		case CommandAction::H_KICK:
			actionsSequence.emplace_front(SpecialAction::H_KICK);
			break;
		default:
			break;
		}
	}

	//Queue has a max of 10 elements
	if (actionsSequence.size() > 10)
	{
		actionsSequence.resize(10);
	}

	actionsSequenceTimer.Resume();
	actionsSequenceTimer.Reset();
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
	if (playerNumber == 1)
		StoreActions(commandData->p1Actions);
	else
		StoreActions(commandData->p2Actions);

	CharacterState* state = CheckSpecialActions();
	if (state != nullptr)
		SetNewState(state);
	else
		SetNewState(currentState->ProcessInput(commandData));

	return true;
}

Entity::Result Character::UpdateState()
{
	if (actionsSequenceTimer.Reached())
	{
		ClearActionsSequence();
	}

	SetNewState(nextState);
	nextState = nullptr;

	SetNewState(currentState->UpdateState());

	return Entity::Result::R_OK;
}

void Character::OnCollitionEnter(Collider * colA, Collider * colB)
{
	//If character are hit deal with it
	if ((colB->type == ColliderType::CHARACTER_ATTACK && colB->listener != this)
		|| colB->type == ColliderType::PARTICLE_ATTACK)
	{
		nextState = currentState->DealHit(colB);
	}

	//If character hit rival disable this frame attack collider to avoid multiple damage
	if (colA->type == ColliderType::CHARACTER_ATTACK 
		&& (colB->type == ColliderType::CHARACTER_BODY && colB->listener != this))
	{
		currentAnimation->DisableCurrentColliderFrame(ColliderType::CHARACTER_ATTACK);
	}
}

AttackInfo Character::GetAttackInfo()
{
	return currentState->GetAttackInfo();
}

void Character::ClearActionsSequence()
{
	actionsSequence.clear();
	actionsSequenceTimer.Pause();
}

void Character::UpdateYPosition()
{
	nextPosition.y -= currentJumpSpeed;
	currentJumpSpeed += gravity;

	if (nextPosition.y > groundLevel)
	{
		nextPosition.y = (float)groundLevel;
		currentJumpSpeed = 0.0f;
	}
}

void Character::MoveXPosition(Direction dir, int speed)
{
	switch (dir)
	{
	case Direction::LEFT:
		nextPosition.x = position.x - (speed * servicesManager->time->frameTimeSeconds);
		break;
	case Direction::RIGHT:
		nextPosition.x = position.x + (speed * servicesManager->time->frameTimeSeconds);
	}
}

void Character::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	currentState->IfMovingForwardRecalculatePositionWithPressingSpeed();
}

void Character::MatchFinished(int playerWin)
{
	SetNewState(currentState->MatchFinished(playerWin));
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
