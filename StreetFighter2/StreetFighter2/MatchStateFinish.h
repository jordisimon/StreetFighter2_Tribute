#pragma once
#include "MatchState.h"

class MatchStateFinish : public MatchState
{
private:
	bool shouldStartAnimations;
	bool finishGUI;
public:
	MatchStateFinish(SceneMatch* s);
	~MatchStateFinish();

	void OnEnter();

	MatchState* UpdateState();
};

