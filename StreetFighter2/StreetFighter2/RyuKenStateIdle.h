#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateIdle :	public RyuKenState
{
private:
	State* ProcessMovement(Direction dir);
	State* ProcessJump(Direction dir);

protected:

	State* ProcessActions(std::vector<CommandAction> actions);
	State* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateIdle(RyuKen* p);
	~RyuKenStateIdle();

	void OnEnter();
	void OnExit();

	State* UpdateState();
};

