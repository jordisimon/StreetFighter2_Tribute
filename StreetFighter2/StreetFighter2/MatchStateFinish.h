#pragma once
#include "MatchState.h"

class MatchStateFinish : public MatchState
{
private:
	bool fading;
public:
	MatchStateFinish(SceneMatch* s);
	~MatchStateFinish();

	void OnEnter();

	MatchState* UpdateState();
};

