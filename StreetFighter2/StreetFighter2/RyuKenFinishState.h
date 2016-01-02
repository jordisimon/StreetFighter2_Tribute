#pragma once
#include "RyuKenState.h"
class RyuKenFinishState : public RyuKenState
{
private:
	bool falling;
	int playerWin;
public:
	RyuKenFinishState(RyuKen* p, int pWin);
	~RyuKenFinishState();

	void OnEnter();

	CharacterState* UpdateState();
};

