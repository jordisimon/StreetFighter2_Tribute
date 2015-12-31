#pragma once
#include "RyuKenState.h"

class RyuKenStateBWalk : public RyuKenState
{
protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);
	CharacterState* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateBWalk(RyuKen* p);
	~RyuKenStateBWalk();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

