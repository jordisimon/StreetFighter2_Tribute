#pragma once
#include "MatchState.h"

class MatchStateIntro :	public MatchState
{
public:
	MatchStateIntro(SceneMatch* s);
	~MatchStateIntro();

	void OnEnter();

	MatchState* UpdateState();
};

