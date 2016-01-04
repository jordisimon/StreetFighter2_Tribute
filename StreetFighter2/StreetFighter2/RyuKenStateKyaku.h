#pragma once
#include "RyuKenState.h"
#include "AttackInfo.h"
#include "Direction.h"

class RyuKenStateKyaku : public RyuKenState
{
private:
	unsigned int step;
	unsigned int speed;
	unsigned int loopsNeeded;
	Direction direction;
	AttackStrength strength;

public:
	RyuKenStateKyaku(RyuKen* p, AttackStrength s);
	~RyuKenStateKyaku();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();

	const AttackInfo GetAttackInfo() const;
};

