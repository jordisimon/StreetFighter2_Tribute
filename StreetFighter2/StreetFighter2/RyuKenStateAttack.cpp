#include "RyuKenStateAttack.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateCrouch.h"


RyuKenStateAttack::RyuKenStateAttack(RyuKen* p, AttackType type) : RyuKenState{ p, false }, attackType { type }
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
		character->SetCurrentAnimation(character->lPunch);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::M_PUNCH:
		character->SetCurrentAnimation(character->mPunch);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::H_PUNCH:
		character->SetCurrentAnimation(character->hPunch);
		character->PlaySfx(character->hAttackSfx);
		break;
	case AttackType::F_L_PUNCH:
		character->SetCurrentAnimation(character->flPunch);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::F_M_PUNCH:
		character->SetCurrentAnimation(character->fmPunch);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::F_H_PUNCH:
		character->SetCurrentAnimation(character->fhPunch);
		character->PlaySfx(character->hAttackSfx);
		break;
	case AttackType::L_KICK:
		character->SetCurrentAnimation(character->lKick);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::M_KICK:
		character->SetCurrentAnimation(character->mKick);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::H_KICK:
		character->SetCurrentAnimation(character->hKick);
		character->PlaySfx(character->hAttackSfx);
		break;
	case AttackType::F_L_KICK:
		character->SetCurrentAnimation(character->flKick);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::F_M_KICK:
		character->SetCurrentAnimation(character->fmKick);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::F_H_KICK:
		character->SetCurrentAnimation(character->fhKick);
		character->PlaySfx(character->hAttackSfx);
		break;
	case AttackType::C_L_PUNCH:
		character->SetCurrentAnimation(character->clPunch);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::C_M_PUNCH:
		character->SetCurrentAnimation(character->cmPunch);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::C_H_PUNCH:
		character->SetCurrentAnimation(character->chPunch);
		character->PlaySfx(character->hAttackSfx);
		break;
	case AttackType::C_L_KICK:
		character->SetCurrentAnimation(character->clKick);
		character->PlaySfx(character->lAttackSfx);
		break;
	case AttackType::C_M_KICK:
		character->SetCurrentAnimation(character->cmKick);
		character->PlaySfx(character->mAttackSfx);
		break;
	case AttackType::C_H_KICK:
		character->SetCurrentAnimation(character->chKick);
		character->PlaySfx(character->hAttackSfx);
		break;
	default:
		break;
	}
	
	character->isAttacking = true;
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
		default:
			return new RyuKenStateIdle(character);
			break;
		}
	}

	return nullptr;
}

const AttackInfo RyuKenStateAttack::GetAttackInfo() const
{
	AttackInfo attackInfo;

	attackInfo.type = attackType;

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
