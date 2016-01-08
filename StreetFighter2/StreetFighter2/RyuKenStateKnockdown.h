#pragma once
#include "RyuKenState.h"
#include "Direction.h"
#include "Timer.h"

class Particle;

class RyuKenStateKnockdown : public RyuKenState
{
private:
	unsigned int step;

public:
	RyuKenStateKnockdown(RyuKen* p);
	~RyuKenStateKnockdown();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

