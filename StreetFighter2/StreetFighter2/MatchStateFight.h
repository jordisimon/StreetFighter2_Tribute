#pragma once
#include "MatchState.h"
#include "Timer.h"

class MatchStateFight :	public MatchState
{
public:
	MatchStateFight(SceneMatch* s);
	~MatchStateFight();

	void OnEnter();
	void OnExit();

	State* ProcessInput(CommandData* commandData);
	State* UpdateState();
};

