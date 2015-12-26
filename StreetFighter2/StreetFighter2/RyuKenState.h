#pragma once
#include "State.h"
#include <vector>
#include "CommandAction.h"
#include "CommandState.h"

class RyuKen;

class RyuKenState :	public State
{
protected:
	RyuKen* character = nullptr;

	virtual State* ProcessActions(std::vector<CommandAction> actions) { return nullptr; };
	virtual State* ProcessStates(std::vector<CommandState> states) { return nullptr; };

public:
	RyuKenState(RyuKen* p);
	~RyuKenState();

	State* ProcessInput(CommandData* commandData);
};

