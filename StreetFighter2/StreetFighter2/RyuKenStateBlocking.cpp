#include "RyuKenStateBlocking.h"
#include "RyuKen.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateWalk.h"
#include "RyuKenStateAttack.h"
#include "Collider.h"
#include "ColliderType.h"
#include "ServicesManager.h"
#include "ServiceParticles.h"
#include "ParticleAttack.h"
#include "AttackInfo.h"
#include "ParticleInfo.h"
#include "RyuKenStateKyaku.h"


CharacterState * RyuKenStateBlocking::ProcessActions(std::vector<CommandAction> actions)
{
	bool closeRange = character->rivalDistance < (character->fMargin * 2) + 10;
	for (const auto& command : actions)
	{
		switch (command)
		{
		case CommandAction::L_PUNCH:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_L_PUNCH);
			else
				return new RyuKenStateAttack(character, AttackType::L_PUNCH);
			break;
		case CommandAction::M_PUNCH:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_M_PUNCH);
			else
				return new RyuKenStateAttack(character, AttackType::M_PUNCH);
			break;
		case CommandAction::H_PUNCH:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_H_PUNCH);
			else
				return new RyuKenStateAttack(character, AttackType::H_PUNCH);
			break;
		case CommandAction::L_KICK:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_L_KICK);
			else
				return new RyuKenStateAttack(character, AttackType::L_KICK);
			break;
		case CommandAction::M_KICK:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_M_KICK);
			else
				return new RyuKenStateAttack(character, AttackType::M_KICK);
			break;
		case CommandAction::H_KICK:
			if (closeRange)
				return new RyuKenStateAttack(character, AttackType::F_H_KICK);
			else
				return new RyuKenStateAttack(character, AttackType::H_KICK);
			break;
		}
	}
	return nullptr;
}

CharacterState * RyuKenStateBlocking::ProcessStates(std::vector<CommandState> states)
{
	bool keepBlocking = false;
	bool walkingForward = false;
	Direction dir;

	for (const auto& command : states)
	{
		switch (command)
		{
		case CommandState::MOVE_LEFT:
			if(character->direction == Direction::RIGHT)
				keepBlocking = true;
			else
				walkingForward = true;
			dir = Direction::LEFT;
			break;

		case CommandState::MOVE_RIGHT:
			if (character->direction == Direction::LEFT)
				keepBlocking = true;
			else
				walkingForward = true;
			break;
		}
	}

	if (!keepBlocking)
	{
		if (walkingForward)
			return new RyuKenStateWalk(character, true);
		else
			return new RyuKenStateIdle(character);
	}

	return nullptr;
}

RyuKenStateBlocking::RyuKenStateBlocking(RyuKen* p) : RyuKenState{p}
{
}


RyuKenStateBlocking::~RyuKenStateBlocking()
{
}

void RyuKenStateBlocking::OnEnter()
{
	character->currentAnimation = &character->blocking;
	RyuKenState::OnEnter();
}

CharacterState * RyuKenStateBlocking::UpdateState()
{
	RyuKenState::UpdateState();

	if (!character->isRivalAttacking)
	{
		//Keep walking back
		return new RyuKenStateWalk(character, false);
	}
	return nullptr;
}

CharacterState * RyuKenStateBlocking::DoSpecialAction(const CharacterSpecialAttack & type)
{
	const RyuKenSpecialAttack& specialType = (RyuKenSpecialAttack&)type;

	switch (specialType.type)
	{
	case RyuKenSpecialAttackType::L_KYAKU:
		return new RyuKenStateKyaku(character, AttackStrength::LIGHT);

	case RyuKenSpecialAttackType::M_KYAKU:
		return new RyuKenStateKyaku(character, AttackStrength::MEDIUM);

	case RyuKenSpecialAttackType::H_KYAKU:
		return new RyuKenStateKyaku(character, AttackStrength::HARD);
	}

	return nullptr;
}

CharacterState * RyuKenStateBlocking::DealHit(Collider * collider)
{
	AttackInfo attackInfo;

	if (collider->type == ColliderType::CHARACTER_ATTACK)
	{
		Character* enemy = (Character*)collider->listener;
		attackInfo = enemy->GetAttackInfo();

		//Particle only if hit by rival directly
		ParticleInfo particleInfo;
		particleInfo.direction = character->direction;
		particleInfo.position.x = collider->colliderRect.x;
		particleInfo.position.y = collider->colliderRect.y;
		particleInfo.type = ParticleType::HIT_BLOCKED;
		servicesManager->particles->CreateParticle(particleInfo);	

		character->applyToOtherPlayer = true;
	}
	else if (collider->type == ColliderType::PARTICLE_ATTACK)
	{
		ParticleAttack* particle = (ParticleAttack*)collider->listener;
		attackInfo = particle->GetAttackInfo();

		character->applyToOtherPlayer = false;
	}

	//If special attack, even when blocking we get some damage (about 25%)
	if (attackInfo.special)
	{
		character->life -= attackInfo.damage / 4;
		if (character->life < 0)
			character->life = 0;
	}

	character->hitBackwardMovement = attackInfo.backMovement;
	character->hitBackwardSpeed = attackInfo.backSpeed;
	character->PlaySfx(character->hitBlockedSfx);

	return nullptr;
}
