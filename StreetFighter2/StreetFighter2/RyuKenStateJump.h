#pragma once
#include "RyuKenState.h"

class RyuKenStateJump :	public RyuKenState
{
protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);

public:
	RyuKenStateJump(RyuKen* p);
	~RyuKenStateJump();

	void OnEnter();

	CharacterState* UpdateState();
};

