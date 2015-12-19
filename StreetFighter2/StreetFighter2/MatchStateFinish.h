#pragma once
#include "MatchState.h"
class MatchStateFinish :
	public MatchState
{
public:
	MatchStateFinish(SceneMatch* s);
	~MatchStateFinish();
};

