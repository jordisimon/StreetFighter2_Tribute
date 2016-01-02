#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateDiagonalJump :	public RyuKenState
{
private:
	Direction direction; //It can change while jumping, but we need to finish the jump in the same direction
	bool forward;
	int hSpeed;

protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);

public:
	RyuKenStateDiagonalJump(RyuKen* p, Direction dir);
	~RyuKenStateDiagonalJump();

	void OnEnter();

	CharacterState* UpdateState();

	void IfMovingForwardRecalculatePositionWithPressingSpeed();
};

