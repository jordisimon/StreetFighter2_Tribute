#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateShoulderToss :	public RyuKenState
{
private:
	Direction direction;
	unsigned int step;
public:
	RyuKenStateShoulderToss(RyuKen* p, Direction dir);
	~RyuKenStateShoulderToss();

	void OnEnter();

	CharacterState* UpdateState();
	void Draw() const;
};

