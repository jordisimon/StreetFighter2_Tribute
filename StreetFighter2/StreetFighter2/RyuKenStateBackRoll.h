#pragma once
#include "RyuKenState.h"
#include "Direction.h"
#include "Timer.h"

class RyuKenStateBackRoll :	public RyuKenState
{
private:
	enum class BackRollState
	{
		GRABBING,
		WAITING,
		RECOVERING
	};

	BackRollState state;
	Direction direction;
	unsigned int step;
	Timer timer;

public:
	RyuKenStateBackRoll(RyuKen* p, Direction dir);
	~RyuKenStateBackRoll();

	void OnEnter();

	CharacterState* UpdateState();
};

