#pragma once
#include "MatchState.h"
#include "Timer.h"

class MatchStateFight :	public MatchState
{
public:
	MatchStateFight(SceneMatch* s) : MatchState{ s } {};
	~MatchStateFight() {};

	void OnEnter();

	MatchState* ProcessInput(CommandData* commandData);
	MatchState* UpdateState();
};

