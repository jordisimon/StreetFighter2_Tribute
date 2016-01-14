#pragma once
#include "RyuKenState.h"
#include "Direction.h"
#include "Timer.h"

class RyuKenStateShoulderToss :	public RyuKenState
{
private:
	enum class ShoulderTossState
	{
		GRABBING,
		WAITING
	};

	ShoulderTossState state;
	Direction direction;
	unsigned int step;
	Timer timer;

public:
	RyuKenStateShoulderToss(RyuKen* p, Direction dir);
	~RyuKenStateShoulderToss();

	void OnEnter();

	CharacterState* UpdateState();
};

