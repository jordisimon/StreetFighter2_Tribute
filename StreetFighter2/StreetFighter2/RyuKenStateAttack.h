#pragma once
#include "RyuKenState.h"

enum class AttackType;

class RyuKenStateAttack : public RyuKenState
{
private:
	AttackType attackType;
public:
	RyuKenStateAttack(RyuKen* p, AttackType type);
	~RyuKenStateAttack();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();

	AttackInfo GetAttackInfo();
};

