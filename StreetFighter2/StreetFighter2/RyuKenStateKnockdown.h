#pragma once
#include "RyuKenState.h"
#include "Direction.h"
#include "Timer.h"

class Particle;

class RyuKenStateKnockdown : public RyuKenState
{
private:
	bool strong;
	unsigned int step;

public:
	RyuKenStateKnockdown(RyuKen* p, bool s);
	~RyuKenStateKnockdown();

	void OnEnter();

	CharacterState* UpdateState();
};

