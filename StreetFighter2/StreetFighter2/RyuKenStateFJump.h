#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateFJump : public RyuKenState
{
private:
	float jumpSpeed;
	Direction direction; //It can change while jumping, but we need to finish the jump in the same direction

public:
	RyuKenStateFJump(RyuKen* p);
	~RyuKenStateFJump();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
	void IfMovingForwardRecalculatePositionWithPressingSpeed();
};

