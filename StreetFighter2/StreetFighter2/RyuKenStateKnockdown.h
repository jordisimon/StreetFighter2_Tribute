#pragma once
#include "RyuKenState.h"
#include "Direction.h"
#include "Timer.h"

class Particle;

class RyuKenStateKnockdown : public RyuKenState
{
private:
	Direction animDirection; //Animation can be inverted if character throwed by rival
	unsigned int step;

public:
	RyuKenStateKnockdown(RyuKen* p, Direction animDir);
	~RyuKenStateKnockdown();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

