#pragma once
#include "MatchState.h"

class MatchStatePause :	public MatchState
{
private:
	unsigned int playerPaused;

public:
	MatchStatePause(SceneMatch* s, unsigned int player);
	~MatchStatePause();

	void OnEnter();
	void OnExit();

	State* ProcessInput(CommandData* commandData);
	State* UpdateState();
};



