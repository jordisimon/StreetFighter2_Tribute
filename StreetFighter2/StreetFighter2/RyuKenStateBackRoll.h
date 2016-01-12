#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateBackRoll :	public RyuKenState
{
private:
	enum class BackRollState
	{
		GRABBING,
		ROLLING,
		RELEASE
	};

	Direction direction;
	BackRollState state;
	unsigned int step;

public:
	RyuKenStateBackRoll(RyuKen* p, Direction dir);
	~RyuKenStateBackRoll();

	void OnEnter();

	CharacterState* UpdateState();
	void Draw() const;
};

