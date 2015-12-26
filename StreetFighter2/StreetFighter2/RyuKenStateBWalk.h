#pragma once
#include "RyuKenState.h"

class RyuKenStateBWalk : public RyuKenState
{
protected:
	State* ProcessActions(std::vector<CommandAction> actions);
	State* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateBWalk(RyuKen* p);
	~RyuKenStateBWalk();

	void OnEnter();
	void OnExit();

	State* UpdateState();
};

