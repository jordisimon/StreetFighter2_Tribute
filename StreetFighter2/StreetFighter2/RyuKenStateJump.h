#pragma once
#include "RyuKenState.h"

class RyuKenStateJump :	public RyuKenState
{
private:
	int playerWin;

protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);

public:
	RyuKenStateJump(RyuKen* p);
	~RyuKenStateJump();

	void OnEnter();

	CharacterState* UpdateState();
	CharacterState* RoundFinished(int playerWin);
};

