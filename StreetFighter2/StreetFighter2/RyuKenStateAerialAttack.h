#pragma once
#include "RyuKenState.h"
#include "Direction.h"

enum class AttackType;

class RyuKenStateAerialAttack : public RyuKenState
{
private:
	AttackType attackType;
	bool diagonal;
	Direction direction; //It can change while jumping, but we need to finish the jump in the same direction
	bool forward;
	int hSpeed;

public:
	RyuKenStateAerialAttack(RyuKen* p, AttackType type);
	RyuKenStateAerialAttack(RyuKen* p, AttackType type, Direction dir, bool f, int hSp);
	~RyuKenStateAerialAttack();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();

	void IfMovingForwardRecalculatePositionWithPressingSpeed();

	AttackInfo GetAttackInfo();
};

