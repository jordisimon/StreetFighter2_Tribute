#pragma once
#include "RyuKenState.h"

class RyuKenStateFWalk: public RyuKenState
{
protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);
	CharacterState* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateFWalk(RyuKen* p);
	~RyuKenStateFWalk();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();

	void IfMovingForwardRecalculatePositionWithPressingSpeed();
};

