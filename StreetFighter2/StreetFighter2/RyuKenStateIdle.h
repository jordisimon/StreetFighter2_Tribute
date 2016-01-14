#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateIdle :	public RyuKenState
{
protected:

	CharacterState* ProcessActions(std::vector<CommandAction> actions);
	CharacterState* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateIdle(RyuKen* p);
	~RyuKenStateIdle();

	void OnEnter();
};

