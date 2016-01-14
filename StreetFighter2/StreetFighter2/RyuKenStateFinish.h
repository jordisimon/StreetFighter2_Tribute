#pragma once
#include "RyuKenState.h"

class RyuKenStateFinish : public RyuKenState
{
private:
	bool falling;
	int playerWin;

public:
	RyuKenStateFinish(RyuKen* p, int pWin);
	~RyuKenStateFinish();

	void OnEnter();

	CharacterState* UpdateState();
};

