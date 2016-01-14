#include "RyuKenStateKyaku.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"

RyuKenStateKyaku::RyuKenStateKyaku(RyuKen* p, AttackStrength s) : RyuKenState{ p, false }, strength{ s }
{
	direction = character->direction;
}

RyuKenStateKyaku::~RyuKenStateKyaku()
{
}

void RyuKenStateKyaku::OnEnter()
{
	step = 0;
	character->SetCurrentAnimation(character->kyakuBegin);
	character->isAttacking = true;
	switch (strength)
	{
	case AttackStrength::LIGHT:
		character->PlaySfx(character->lKyakuSfx);
		character->kyakuBegin.SetDuration(0.3f);
		character->kyaku.SetDuration(0.3f);
		character->kyakuEnd.SetDuration(0.3f);
		speed = 55;
		loopsNeeded = 3;
		break;
	case AttackStrength::MEDIUM:
		character->PlaySfx(character->mKyakuSfx);
		character->kyakuBegin.SetDuration(0.25f);
		character->kyaku.SetDuration(0.25f);
		character->kyakuEnd.SetDuration(0.25f);
		speed = 77;
		loopsNeeded = 4;
		break;
	case AttackStrength::HARD:
		character->PlaySfx(character->hKyakuSfx);
		character->kyakuBegin.SetDuration(0.2f);
		character->kyaku.SetDuration(0.2f);
		character->kyakuEnd.SetDuration(0.2f);
		speed = 115;
		loopsNeeded = 5;
		break;
	default:
		break;
	}
}

void RyuKenStateKyaku::OnExit()
{
	RyuKenState::OnExit();
	character->ClearActionsSequence();
	character->isAttacking = false;
}

CharacterState * RyuKenStateKyaku::UpdateState()
{
	RyuKenState::UpdateState();

	character->MoveXPosition(direction, speed);

	switch (step)
	{
	case 0:
		if (character->currentAnimation->HasFinished())
		{
			++step;
			RyuKenState::OnExit();
			character->SetCurrentAnimation(character->kyaku);
		}
		break;

	case 1:
		if (character->currentAnimation->loopsCompleted == loopsNeeded)
		{
			++step;
			RyuKenState::OnExit();
			character->SetCurrentAnimation(character->kyakuEnd);
		}
		break;
	case 2:
		if (character->currentAnimation->HasFinished())
		{
			return new RyuKenStateIdle(character);
		}
	default:
		break;
	}

	return nullptr;
}

const AttackInfo RyuKenStateKyaku::GetAttackInfo() const
{
	AttackInfo attackInfo;

	attackInfo.type = AttackType::SPECIAL;
	attackInfo.strength = strength;

	switch (strength)
	{
	case AttackStrength::LIGHT:
		attackInfo.damage = 14;
		attackInfo.backMovement = 16;
		attackInfo.backSpeed = 32;
		break;
	case AttackStrength::MEDIUM:
		attackInfo.damage = 14;
		attackInfo.backMovement = 26;
		attackInfo.backSpeed = 52;
		break;
	case AttackStrength::HARD:
		attackInfo.damage = 15;
		attackInfo.backMovement = 40;
		attackInfo.backSpeed = 80;
		break;
	default:
		break;
	}

	return attackInfo;
}
