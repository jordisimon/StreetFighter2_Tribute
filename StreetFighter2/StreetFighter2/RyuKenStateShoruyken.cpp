#include "RyuKenStateShoruyken.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"

RyuKenStateShoruyken::RyuKenStateShoruyken(RyuKen* p, AttackStrength s) : RyuKenState{ p, false }, strength{ s }
{
}


RyuKenStateShoruyken::~RyuKenStateShoruyken()
{
}

void RyuKenStateShoruyken::OnEnter()
{
	step = 0;
	character->SetCurrentAnimation(character->shoryukenBegin);
	character->isAttacking = true;
	switch (strength)
	{
	case AttackStrength::LIGHT:
		character->PlaySfx(character->lShoryukenSfx);
		break;
	case AttackStrength::MEDIUM:
		character->PlaySfx(character->mShoryukenSfx);
		break;
	case AttackStrength::HARD:
		character->PlaySfx(character->hShoryukenSfx);
		break;
	default:
		break;
	}
}

void RyuKenStateShoruyken::OnExit()
{
	RyuKenState::OnExit();
	character->ClearActionsSequence();
	character->isAttacking = false;
}

CharacterState* RyuKenStateShoruyken::UpdateState()
{
	RyuKenState::UpdateState();

	switch (step)
	{
	case 0:
		if (character->currentAnimation->HasFinished())
		{
			++step;
			RyuKenState::OnExit();
			character->SetCurrentAnimation(character->shoryuken);
			switch (strength)
			{
			case AttackStrength::LIGHT:
				character->currentJumpSpeed = (float)character->jumpVSpeed * 0.8f;
				break;
			case AttackStrength::MEDIUM:
				character->currentJumpSpeed = (float)character->jumpVSpeed * 0.9f;
				break;
			case AttackStrength::HARD:
				character->currentJumpSpeed = (float)character->jumpVSpeed;
				break;
			default:
				break;
			}
		}
		break;

	case 1:
		if (character->currentJumpSpeed > 0.0f)
		{
			++step;
			RyuKenState::OnExit();
			character->SetCurrentAnimation(character->shoryukenEnd);
		}
	case 2:
		if (character->nextPosition.y >= character->groundLevel)
		{
			return new RyuKenStateIdle(character);
		}
	default:
		break;
	}

	return nullptr;
}

const AttackInfo RyuKenStateShoruyken::GetAttackInfo() const
{
	AttackInfo attackInfo;

	attackInfo.type = AttackType::SPECIAL;
	attackInfo.strength = strength;

	switch (strength)
	{
	case AttackStrength::LIGHT:
		attackInfo.damage = 12;
		attackInfo.backMovement = 16;
		attackInfo.backSpeed = 32;
		break;
	case AttackStrength::MEDIUM:
		attackInfo.damage = 16;
		attackInfo.backMovement = 26;
		attackInfo.backSpeed = 52;
		break;
	case AttackStrength::HARD:
		attackInfo.damage = 22;
		attackInfo.backMovement = 40;
		attackInfo.backSpeed = 80;
		break;
	default:
		break;
	}

	return attackInfo;
}
