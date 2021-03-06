#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateAerialHit : public RyuKenState
{
private:
	Direction direction; //It can change while jumping, but we need to finish the jump in the same direction
	int playerWin;

public:
	RyuKenStateAerialHit(RyuKen* p);
	~RyuKenStateAerialHit();

	void OnEnter();

	CharacterState* UpdateState();
	CharacterState* RoundFinished(int playerWin);
};

