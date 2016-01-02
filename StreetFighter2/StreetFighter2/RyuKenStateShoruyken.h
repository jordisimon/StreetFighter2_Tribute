#pragma once
#include "RyuKenState.h"
#include "AttackInfo.h"

class RyuKenStateShoruyken : public RyuKenState
{
private:
	unsigned int step;
	AttackStrength strength;
public:
	RyuKenStateShoruyken(RyuKen* p, AttackStrength s);
	~RyuKenStateShoruyken();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();

	AttackInfo GetAttackInfo();
};

