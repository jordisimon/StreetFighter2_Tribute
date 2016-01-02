#include "RyuKenStateAerialAttack.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"

RyuKenStateAerialAttack::RyuKenStateAerialAttack(RyuKen * p, AttackType type) : RyuKenState{ p }, attackType{ type }, forward{true}, hSpeed{0}, diagonal{ false }
{
	direction = character->direction;
}

RyuKenStateAerialAttack::RyuKenStateAerialAttack(RyuKen* p, AttackType type, Direction dir, bool f, int hSp) : RyuKenState{ p }, attackType{ type }, direction { dir }, forward{ f }, hSpeed{ hSp }, diagonal{ true }
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
		character->currentAnimation = &character->jlPunch;
		break;
	case AttackType::J_M_PUNCH:
		character->currentAnimation = &character->jmPunch;
		break;
	case AttackType::J_H_PUNCH:
		character->currentAnimation = &character->jhPunch;
		break;
	case AttackType::F_J_L_PUNCH:
		character->currentAnimation = &character->fjlPunch;
		break;
	case AttackType::F_J_M_PUNCH:
		character->currentAnimation = &character->fjmPunch;
		break;
	case AttackType::F_J_H_PUNCH:
		character->currentAnimation = &character->fjhPunch;
		break;
	case AttackType::J_L_KICK:
		character->currentAnimation = &character->jlKick;
		break;
	case AttackType::J_M_KICK:
		character->currentAnimation = &character->jmKick;
		break;
	case AttackType::J_H_KICK:
		character->currentAnimation = &character->jhKick;
		break;
	case AttackType::F_J_L_KICK:
		character->currentAnimation = &character->fjlKick;
		break;
	case AttackType::F_J_M_KICK:
		character->currentAnimation = &character->fjmKick;
		break;
	case AttackType::F_J_H_KICK:
		character->currentAnimation = &character->fjhKick;
		break;
	default:
		break;
	}

	character->isAttacking = true;
	character->PlaySfx(character->attackSfx);
	RyuKenState::OnEnter();
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
		return new RyuKenStateIdle(character);
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}

void RyuKenStateAerialAttack::IfMovingForwardRecalculatePositionWithPressingSpeed()
{
	if (forward)
		character->MoveXPosition(character->direction, character->pSpeed);
}

AttackInfo RyuKenStateAerialAttack::GetAttackInfo()
{
	AttackInfo attackInfo;

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
