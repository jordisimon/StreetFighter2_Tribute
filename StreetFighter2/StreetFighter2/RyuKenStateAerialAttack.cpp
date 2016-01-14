#include "RyuKenStateAerialAttack.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateFinish.h"

RyuKenStateAerialAttack::RyuKenStateAerialAttack(RyuKen * p, AttackType type) : RyuKenState{ p, false }, attackType{ type }, forward{ true }, hSpeed{ 0 }, diagonal{ false }, playerWin{ -1 }
{
	direction = character->direction;
}

RyuKenStateAerialAttack::RyuKenStateAerialAttack(RyuKen* p, AttackType type, Direction dir, bool f, int hSp) : RyuKenState{ p, false }, attackType{ type }, direction { dir }, forward{ f }, hSpeed{ hSp }, diagonal{ true }, playerWin{ -1 }
{
}


RyuKenStateAerialAttack::~RyuKenStateAerialAttack()
{
}

void RyuKenStateAerialAttack::OnEnter()
{
	switch (attackType)
	{
	case AttackType::J_L_PUNCH:
		character->SetCurrentAnimation(character->jlPunch, character->animDirection);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::J_M_PUNCH:
		character->SetCurrentAnimation(character->jmPunch, character->animDirection);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::J_H_PUNCH:
		character->SetCurrentAnimation(character->jhPunch, character->animDirection);
		character->PlaySfx(character->hAttackSfx);
		break;
	case AttackType::F_J_L_PUNCH:
		character->SetCurrentAnimation(character->fjlPunch, character->animDirection);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::F_J_M_PUNCH:
		character->SetCurrentAnimation(character->fjmPunch, character->animDirection);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::F_J_H_PUNCH:
		character->SetCurrentAnimation(character->fjhPunch, character->animDirection);
		character->PlaySfx(character->hAttackSfx);
		break;
	case AttackType::J_L_KICK:
		character->SetCurrentAnimation(character->jlKick, character->animDirection);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::J_M_KICK:
		character->SetCurrentAnimation(character->jmKick, character->animDirection);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::J_H_KICK:
		character->SetCurrentAnimation(character->jhKick, character->animDirection);
		character->PlaySfx(character->hAttackSfx);
		break;
	case AttackType::F_J_L_KICK:
		character->SetCurrentAnimation(character->fjlKick, character->animDirection);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::F_J_M_KICK:
		character->SetCurrentAnimation(character->fjmKick, character->animDirection);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::F_J_H_KICK:
		character->SetCurrentAnimation(character->fjhKick, character->animDirection);
		character->PlaySfx(character->hAttackSfx);
		break;
	default:
		break;
	}

	character->isAttacking = true;
}

void RyuKenStateAerialAttack::OnExit()
{
	RyuKenState::OnExit();
	character->isAttacking = false;
}

CharacterState * RyuKenStateAerialAttack::UpdateState()
{
	RyuKenState::UpdateState();

	if (diagonal)
	{
		character->MoveXPosition(direction, hSpeed);
	}

	//Aerial attacks finish when landing
	if (character->nextPosition.y >= character->groundLevel)
	{
		character->PlaySfx(character->floorHit2Sfx);
		if (playerWin < 0)
			return new RyuKenStateIdle(character);
		else
			return new RyuKenStateFinish(character, playerWin);
	}

	return nullptr;
}

CharacterState * RyuKenStateAerialAttack::RoundFinished(int playerWin)
{
	if (character->life > 0)
	{
		//Store winner (change state when back to ground)
		this->playerWin = playerWin;
		return nullptr;
	}
	else
	{
		return new RyuKenStateFinish(character, playerWin);
	}
}

void RyuKenStateAerialAttack::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	if (forward)
		character->MoveXPosition(character->direction, character->pSpeed);
}

const AttackInfo RyuKenStateAerialAttack::GetAttackInfo() const
{
	AttackInfo attackInfo;

	attackInfo.type = attackType;

	switch (attackType)
	{
	case AttackType::J_L_PUNCH:
	case AttackType::F_J_L_PUNCH:
	case AttackType::J_L_KICK:
	case AttackType::F_J_L_KICK:
		attackInfo.strength = AttackStrength::LIGHT;
		attackInfo.damage = 10;
		attackInfo.backMovement = 16;
		attackInfo.backSpeed = 32;
		break;
	case AttackType::J_M_PUNCH:
	case AttackType::F_J_M_PUNCH:
	case AttackType::J_M_KICK:
	case AttackType::F_J_M_KICK:
		attackInfo.strength = AttackStrength::MEDIUM;
		attackInfo.damage = 15;
		attackInfo.backMovement = 26;
		attackInfo.backSpeed = 52;
		break;
	case AttackType::J_H_PUNCH:
	case AttackType::F_J_H_PUNCH:
	case AttackType::J_H_KICK:
	case AttackType::F_J_H_KICK:
		attackInfo.strength = AttackStrength::HARD;
		attackInfo.damage = 19;
		attackInfo.backMovement = 40;
		attackInfo.backSpeed = 80;
		break;
	
	default:
		break;
	}

	return attackInfo;
}
