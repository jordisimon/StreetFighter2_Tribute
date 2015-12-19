#pragma once
#include "MatchState.h"
#include "MatchStateFight.h"
#include "Timer.h"

class MatchStateIntro :	public MatchState
{
private:
	Timer timer;
	unsigned int step;

public:
	MatchStateIntro(SceneMatch* s);
	~MatchStateIntro();

	void OnEnter();

	State* UpdateState();
};

