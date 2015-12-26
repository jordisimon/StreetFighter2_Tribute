#pragma once
#include "RyuKenState.h"

class RyuKenStateFWalk: public RyuKenState
{
protected:
	State* ProcessActions(std::vector<CommandAction> actions);
	State* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateFWalk(RyuKen* p);
	~RyuKenStateFWalk();

	void OnEnter();
	void OnExit();

	State* UpdateState();
};

