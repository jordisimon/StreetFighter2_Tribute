#pragma once
#include "RyuKenState.h"
#include "Timer.h"

class RyuKenStateHadoken : public RyuKenState
{
private:
	unsigned int step;
	AttackStrength strength;
	Timer timer;

public:
	RyuKenStateHadoken(RyuKen* p, AttackStrength s);
	~RyuKenStateHadoken();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

