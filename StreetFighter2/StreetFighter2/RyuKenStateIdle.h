#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateIdle :	public RyuKenState
{
private:
	CharacterState* ProcessMovement(Direction dir);
	CharacterState* ProcessJump(Direction dir);

protected:

	CharacterState* ProcessActions(std::vector<CommandAction> actions);
	CharacterState* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateIdle(RyuKen* p);
	~RyuKenStateIdle();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

