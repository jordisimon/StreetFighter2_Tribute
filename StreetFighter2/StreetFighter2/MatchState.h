#pragma once
#include "State.h"

class SceneMatch;

class MatchState : public State
{
protected:
	SceneMatch* scene = nullptr;

public:
	MatchState(SceneMatch* s);
	~MatchState();
};

