#include "RyuKenStateAttack.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateCrouch.h"


RyuKenStateAttack::RyuKenStateAttack(RyuKen* p, AttackType type) : RyuKenState{ p }, attackType { type }
{
}


RyuKenStateAttack::~RyuKenStateAttack()
{
}

void RyuKenStateAttack::OnEnter()
{
	switch (attackType)
	{
	case AttackType::L_PUNCH:
		character->currentAnimation = &character->lPunch;
		break;
	case AttackType::M_PUNCH:
		character->currentAnimation = &character->mPunch;
		break;
	case AttackType::H_PUNCH:
		character->currentAnimation = &character->hPunch;
		break;
	case AttackType::F_L_PUNCH:
		character->currentAnimation = &character->flPunch;
		break;
	case AttackType::F_M_PUNCH:
		character->currentAnimation = &character->fmPunch;
		break;
	case AttackType::F_H_PUNCH:
		character->currentAnimation = &character->fhPunch;
		break;
	case AttackType::L_KICK:
		character->currentAnimation = &character->lKick;
		break;
	case AttackType::M_KICK:
		character->currentAnimation = &character->mKick;
		break;
	case AttackType::H_KICK:
		character->currentAnimation = &character->hKick;
		break;
	case AttackType::F_L_KICK:
		character->currentAnimation = &character->flKick;
		break;
	case AttackType::F_M_KICK:
		character->currentAnimation = &character->fmKick;
		break;
	case AttackType::F_H_KICK:
		character->currentAnimation = &character->fhKick;
		break;
	case AttackType::C_L_PUNCH:
		character->currentAnimation = &character->clPunch;
		break;
	case AttackType::C_M_PUNCH:
		character->currentAnimation = &character->cmPunch;
		break;
	case AttackType::C_H_PUNCH:
		character->currentAnimation = &character->chPunch;
		break;
	case AttackType::C_L_KICK:
		character->currentAnimation = &character->clKick;
		break;
	case AttackType::C_M_KICK:
		character->currentAnimation = &character->cmKick;
		break;
	case AttackType::C_H_KICK:
		character->currentAnimation = &character->chKick;
		break;
	default:
		break;
	}
	
	character->isAttacking = true;
	character->PlaySfx(character->attackSfx);
	RyuKenState::OnEnter();
}

void RyuKenStateAttack::OnExit()
{
	RyuKenState::OnExit();
	character->isAttacking = false;
}

CharacterState * RyuKenStateAttack::UpdateState()
{
	RyuKenState::UpdateState();

	if (character->currentAnimation->HasFinished())
	{
		switch (attackType)
		{
		//Ground attacks finishes when animation done
		case AttackType::L_PUNCH:
		case AttackType::M_PUNCH:
		case AttackType::H_PUNCH:
		case AttackType::F_L_PUNCH:
		case AttackType::F_M_PUNCH:
		case AttackType::F_H_PUNCH:
		case AttackType::L_KICK:
		case AttackType::M_KICK:
		case AttackType::H_KICK:
		case AttackType::F_L_KICK:
		case AttackType::F_M_KICK:
		case AttackType::F_H_KICK:
			return new RyuKenStateIdle(character);
			break;
		case AttackType::C_L_PUNCH:
		case AttackType::C_M_PUNCH:
		case AttackType::C_H_PUNCH:
		case AttackType::C_L_KICK:
		case AttackType::C_M_KICK:
		case AttackType::C_H_KICK:
			return new RyuKenStateCrouch(character, false);
			break;
		}
	}

	character->currentAnimation->UpdateCurrentFrame(character->position, character->direction);
	return nullptr;
}

AttackInfo RyuKenStateAttack::GetAttackInfo()
{
	AttackInfo attackInfo;

	switch (attackType)
	{
	case AttackType::L_PUNCH:
	case AttackType::F_L_PUNCH:
	case AttackType::L_KICK:
	case AttackType::F_L_KICK:
		attackInfo.strength = AttackStrength::LIGHT;
		attackInfo.damage = 10;
		attackInfo.backMovement = 16;
		attackInfo.backSpeed = 32;
		break;
	case AttackType::M_PUNCH:
	case AttackType::F_M_PUNCH:
	case AttackType::M_KICK:
	case AttackType::F_M_KICK:
		attackInfo.strength = AttackStrength::MEDIUM;
		attackInfo.damage = 14;
		attackInfo.backMovement = 26;
		attackInfo.backSpeed = 52;
		break;
	case AttackType::H_PUNCH:
	case AttackType::F_H_PUNCH:
	case AttackType::H_KICK:
	case AttackType::F_H_KICK:
		attackInfo.strength = AttackStrength::HARD;
		attackInfo.damage = 19;
		attackInfo.backMovement = 40;
		attackInfo.backSpeed = 80;
		break;

	case AttackType::C_L_PUNCH:
	case AttackType::C_L_KICK:
		attackInfo.strength = AttackStrength::LIGHT;
		attackInfo.damage = 9;
		attackInfo.backMovement = 16;
		attackInfo.backSpeed = 32;
		break;
	case AttackType::C_M_PUNCH:
	case AttackType::C_M_KICK:
		attackInfo.strength = AttackStrength::MEDIUM;
		attackInfo.damage = 14;
		attackInfo.backMovement = 26;
		attackInfo.backSpeed = 52;
		break;
	case AttackType::C_H_PUNCH:
	case AttackType::C_H_KICK:
		attackInfo.strength = AttackStrength::HARD;
		attackInfo.damage = 17;
		attackInfo.backMovement = 40;
		attackInfo.backSpeed = 80;
		break;

	default:
		break;
	}

	return attackInfo;
}
