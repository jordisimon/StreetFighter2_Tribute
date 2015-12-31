#pragma once
#include "RyuKenState.h"

class RyuKenStateBJump : public RyuKenState
{
private:
	float jumpSpeed;
public:
	RyuKenStateBJump(RyuKen* p);
	~RyuKenStateBJump();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
	void IfMovingForwardRecalculatePositionWithPressingSpeed();
};

