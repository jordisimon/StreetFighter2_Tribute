#include "Character.h"
#include "Defines.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceAudio.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"
#include "ServiceTime.h"
#include "Particle.h"
#include "CharacterState.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "CommandState.h"
#include "Collider.h"
#include "ColliderType.h"
#include "SF2Stats.h"

int Character::lAttackSfx = -1;
int Character::mAttackSfx = -1;
int Character::hAttackSfx = -1;
int Character::lHitSfx = -1;
int Character::mHitSfx = -1;
int Character::hHitSfx = -1;
int Character::hitBlockedSfx = -1;
int Character::floorHitSfx = -1;
int Character::floorHit2Sfx = -1;

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
	height = config->LoadFloatValue(configSection, "height", "0");
	fMargin = config->LoadFloatValue(configSection, "fMargin", "0");
	bMargin = config->LoadFloatValue(configSection, "bMargin", "0");

	config->LoadSprite(shadow, configSection, "shadow");

	if (lAttackSfx == -1) lAttackSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\lAttack.ogg");
	if (mAttackSfx == -1) mAttackSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\mAttack.ogg");
	if (hAttackSfx == -1) hAttackSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\hAttack.ogg");
	if (lHitSfx == -1) lHitSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\lHit.ogg");
	if (mHitSfx == -1) mHitSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\mHit.ogg");
	if (hHitSfx == -1) hHitSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\hHit.ogg");
	if (hitBlockedSfx == -1) hitBlockedSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\hitBlocked.ogg");
	if (floorHitSfx == -1) floorHitSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\floorHit.ogg");
	if (floorHit2Sfx == -1) floorHit2Sfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\floorHit2.ogg");

	//Moving
	config->LoadAnimationCollider(idle, configSection, "idle");
	idle.listener = this;
	config->LoadAnimationCollider(fWalk, configSection, "fWalk");
	fWalk.listener = this;
	config->LoadAnimationCollider(bWalk, configSection, "bWalk");
	bWalk.listener = this;
	config->LoadAnimationCollider(jump, configSection, "jump");
	jump.listener = this;
	config->LoadAnimationCollider(fJump, configSection, "fJump");
	fJump.listener = this;
	config->LoadAnimationCollider(bJump, configSection, "bJump");
	bJump.listener = this;
	config->LoadAnimationCollider(crouch, configSection, "crouch");
	crouch.listener = this;
	config->LoadAnimationCollider(blocking, configSection, "blocking");
	blocking.listener = this;
	config->LoadAnimationCollider(cBlocking, configSection, "cBlocking");
	cBlocking.listener = this;

	//Hit
	config->LoadAnimationCollider(hit, configSection, "hit");
	hit.listener = this;
	config->LoadAnimationCollider(faceHit, configSection, "faceHit");
	faceHit.listener = this;
	config->LoadAnimationCollider(cHit, configSection, "cHit");
	cHit.listener = this;
	config->LoadAnimationCollider(aHit, configSection, "aHit");
	aHit.listener = this;

	//Attack (punch)
	//Standing
	config->LoadAnimationCollider(lPunch, configSection, "lPunch");
	lPunch.listener = this;
	config->LoadAnimationCollider(mPunch, configSection, "mPunch");
	mPunch.listener = this;
	config->LoadAnimationCollider(hPunch, configSection, "hPunch");
	hPunch.listener = this;

	//Close range
	config->LoadAnimationCollider(flPunch, configSection, "flPunch");
	flPunch.listener = this;
	config->LoadAnimationCollider(fmPunch, configSection, "fmPunch");
	fmPunch.listener = this;
	config->LoadAnimationCollider(fhPunch, configSection, "fhPunch");
	fhPunch.listener = this;

	//Crouching
	config->LoadAnimationCollider(clPunch, configSection, "clPunch");
	clPunch.listener = this;
	config->LoadAnimationCollider(cmPunch, configSection, "cmPunch");
	cmPunch.listener = this;
	config->LoadAnimationCollider(chPunch, configSection, "chPunch");
	chPunch.listener = this;

	//Straight jump
	config->LoadAnimationCollider(jlPunch, configSection, "jlPunch");
	jlPunch.listener = this;
	config->LoadAnimationCollider(jmPunch, configSection, "jmPunch");
	jmPunch.listener = this;
	config->LoadAnimationCollider(jhPunch, configSection, "jhPunch");
	jhPunch.listener = this;

	//Diagonal jump
	//Not bug SNES anims are the same as straigh jump
	config->LoadAnimationCollider(fjlPunch, configSection, "jlPunch");
	fjlPunch.listener = this;
	config->LoadAnimationCollider(fjmPunch, configSection, "jmPunch");
	fjmPunch.listener = this;
	config->LoadAnimationCollider(fjhPunch, configSection, "jhPunch");
	fjhPunch.listener = this;

	//Attack (kick)
	//Standing
	config->LoadAnimationCollider(lKick, configSection, "lKick");
	lKick.listener = this;
	config->LoadAnimationCollider(mKick, configSection, "mKick");
	mKick.listener = this;
	config->LoadAnimationCollider(hKick, configSection, "hKick");
	hKick.listener = this;

	//Close range
	config->LoadAnimationCollider(flKick, configSection, "flKick");
	flKick.listener = this;
	config->LoadAnimationCollider(fmKick, configSection, "fmKick");
	fmKick.listener = this;
	config->LoadAnimationCollider(fhKick, configSection, "fhKick");
	fhKick.listener = this;

	//Crouching
	config->LoadAnimationCollider(clKick, configSection, "clKick");
	clKick.listener = this;
	config->LoadAnimationCollider(cmKick, configSection, "cmKick");
	cmKick.listener = this;
	config->LoadAnimationCollider(chKick, configSection, "chKick");
	chKick.listener = this;

	//Straight jump
	config->LoadAnimationCollider(jlKick, configSection, "jlKick");
	jlKick.listener = this;
	config->LoadAnimationCollider(jmKick, configSection, "jmKick");
	jmKick.listener = this;
	config->LoadAnimationCollider(jhKick, configSection, "jhKick");
	jhKick.listener = this;

	//Diagonal jump
	config->LoadAnimationCollider(fjlKick, configSection, "fjlKick");
	fjlKick.listener = this;
	config->LoadAnimationCollider(fjmKick, configSection, "fjmKick");
	fjmKick.listener = this;
	config->LoadAnimationCollider(fjhKick, configSection, "fjhKick");
	fjhKick.listener = this;

	//Knockdown
	config->LoadAnimationCollider(knockdown, configSection, "knockdown");
	knockdown.listener = this;
	config->LoadAnimationCollider(knockdownRecover, configSection, "knockdownRecover");
	knockdownRecover.listener = this;
	config->LoadAnimationCollider(stunned, configSection, "stunned");
	stunned.listener = this;

	//Finish
	config->LoadAnimationCollider(KOBegin, configSection, "KOBegin");
	KOBegin.listener = this;
	config->LoadAnimationCollider(KOEnd, configSection, "KOEnd");
	KOEnd.listener = this;
	config->LoadAnimationCollider(victory1, configSection, "victory1");
	victory1.listener = this;
	config->LoadAnimationCollider(victory2, configSection, "victory2");
	victory2.listener = this;
	config->LoadAnimationCollider(timeover, configSection, "timeover");
	timeover.listener = this;

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
	applyBackwardMovementToOtherPlayerRatio = 0.0f;
	knockdownDamage = 0;
	knockdownTimer.Pause();
	updateOverallSpeed = 1.0f;
	yUpdateControl = 0.0f;
	isAttacking = false;
	isGrabbed = false;

	if (currentAttackParticle != nullptr)
	{
		currentAttackParticle->toDelete = true;
		currentAttackParticle = nullptr;
	}

	if (particleStunned != nullptr)
	{
		particleStunned->toDelete = true;
		particleStunned = nullptr;
	}

	return true;
}

bool Character::Stop()
{
	ClearActionsSequence();

	if (currentAttackParticle != nullptr)
	{
		currentAttackParticle->toDelete = true;
		currentAttackParticle = nullptr;
	}

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

	if (knockdownTimer.Reached())
	{
		knockdownDamage = 0;
		knockdownTimer.Pause();
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
		fRect intersectionRect = colA->colliderRect.GetIntersectionRect(colB->colliderRect);
		nextState = currentState->DealHit(colB, intersectionRect);
	}

	//If character hit rival disable this frame attack collider to avoid multiple damage
	//and stop the attack animation for a brief period
	if (colA->type == ColliderType::CHARACTER_ATTACK 
		&& (colB->type == ColliderType::CHARACTER_BODY && colB->listener != this))
	{
		currentAnimation->DisableCurrentColliderFrame(ColliderType::CHARACTER_ATTACK);
		currentAnimation->ChangeSpeedTemporal(0.0f, 150);
	}
}

void Character::PlaySfx(int sfx) const
{
	servicesManager->audio->PlayFx(sfx);
}

const AttackInfo Character::GetAttackInfo() const
{
	AttackInfo info = currentState->GetAttackInfo();

	if (handicap != 3)
	{
		switch (handicap)
		{
		case 0:
			info.damage = (int)(info.damage * 0.85f);
			break;
		case 1:
			info.damage = (int)(info.damage * 0.8f);
			break;
		case 2:
			info.damage = (int)(info.damage * 0.95f);
			break;
		case 4:
			info.damage = (int)(info.damage * 1.05f);
			break;
		case 5:
			info.damage = (int)(info.damage * 1.1f);
			break;
		case 6:
			info.damage = (int)(info.damage * 1.15f);
			break;
		case 7:
			info.damage = (int)(info.damage * 1.2f);
			break;
		default:
			break;
		}
	}

	return info;
}

void Character::PauseAllTimers()
{
	actionsSequenceTimer.Pause();
	knockdownTimer.Pause();
	stunnedTimer.Pause();
}

void Character::ResumeAllTimers()
{
	actionsSequenceTimer.Resume();
	knockdownTimer.Resume();
	stunnedTimer.Resume();
}

void Character::SubstractDamage(int damage)
{
	life -= damage;
	if (life < 0)
		life = 0;
}

void Character::ClearActionsSequence()
{
	actionsSequence.clear();
	actionsSequenceTimer.Pause();
}

void Character::UpdateYPosition()
{
	yUpdateControl += updateOverallSpeed;

	while (yUpdateControl >= 1.0f)
	{
		nextPosition.y -= currentJumpSpeed;
		currentJumpSpeed += gravity;

		if (nextPosition.y > groundLevel)
		{
			nextPosition.y = (float)groundLevel;
			currentJumpSpeed = 0.0f;
		}
		yUpdateControl -= 1.0f;
	}
}

void Character::MoveXPosition(Direction dir, int speed)
{
	switch (dir)
	{
	case Direction::LEFT:
		nextPosition.x = position.x - ((speed * servicesManager->time->frameTimeSeconds) * updateOverallSpeed);
		break;
	case Direction::RIGHT:
		nextPosition.x = position.x + ((speed * servicesManager->time->frameTimeSeconds) * updateOverallSpeed);
	}
}

void Character::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	currentState->IfMovingForwardRecalculatePositionWithPressingSpeed();
}

void Character::RoundFinished(int playerWin)
{
	SetNewState(currentState->RoundFinished(playerWin));
}

void Character::MatchFinished(int playerWin)
{
	PlayerStats* pStats;
	if (playerNumber == 1)
		pStats = &SF2Stats::p1Stats;
	else
		pStats = &SF2Stats::p2Stats;

	CharacterStats* cStats;
	switch (characterId)
	{
	case 0:
		cStats = &pStats->Ryu;
		break;
	case 1:
		cStats = &pStats->Honda;
		break;
	case 2:
		cStats = &pStats->Blanka;
		break;
	case 3:
		cStats = &pStats->Guile;
		break;
	case 4:
		cStats = &pStats->Ken;
		break;
	case 5:
		cStats = &pStats->Chunli;
		break;
	case 6:
		cStats = &pStats->Zanguief;
		break;
	case 7:
		cStats = &pStats->Dalshim;
		break;
	default:
		cStats = &pStats->Ryu; //To avoid uninitalized warning
		break;
	}

	if (playerWin == playerNumber)
	{
		++pStats->wins;
		++cStats->wins;
	} 
	else if (playerWin == 0)
	{
		++pStats->draws;
		++cStats->draws;
	}
	else
	{
		++pStats->loses;
		++cStats->loses;
	}
}

bool Character::RivalDistanceLowerThan(float minimumDistance)
{
	return position.DistanceXTo(rival->position) < minimumDistance;
}

bool Character::RivalParticleDistanceLowerThan(float minimumDistance)
{
	if ((rival->currentAttackParticle != nullptr) && (rival->currentAttackParticle->toDelete == false))
		return position.DistanceXTo(rival->currentAttackParticle->position) < minimumDistance;
	else
		return false;
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
	currentState->Draw();

	return Entity::Result::R_OK;
}

void Character::DrawDefault(Direction drawDirection) const
{
	servicesManager->render->BlitScene(texture, currentAnimation->GetFrame().GetRectPosition(position, drawDirection), currentAnimation->GetFrame().rect, 1.0f, drawDirection);

	if (servicesManager->debug)
	{
		servicesManager->render->SetDrawColor(Color(Color::Predefined::MAGENTA));
		servicesManager->render->DrawRectFill({ position.x - 1, position.y - 1, 2, 2 });
	}
}
