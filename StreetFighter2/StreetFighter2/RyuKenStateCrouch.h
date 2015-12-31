#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateCrouch : public RyuKenState
{
private: 
	bool defending;
	CharacterState* RyuKenStateCrouch::ProcessMovement(Direction dir);

protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);
	CharacterState* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateCrouch(RyuKen* p, bool def);
	~RyuKenStateCrouch();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

