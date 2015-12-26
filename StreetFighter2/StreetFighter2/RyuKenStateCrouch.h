#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateCrouch : public RyuKenState
{
private: 
	bool defending;
	State* RyuKenStateCrouch::ProcessMovement(Direction dir);

protected:
	State* ProcessActions(std::vector<CommandAction> actions);
	State* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateCrouch(RyuKen* p, bool def);
	~RyuKenStateCrouch();

	void OnEnter();
	void OnExit();

	State* UpdateState();
};

