#pragma once
#include "RyuKenState.h"
class RyuKenStateStunned : public RyuKenState
{
private:
	bool canReduceTime;

protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);

public:
	RyuKenStateStunned(RyuKen* p);
	~RyuKenStateStunned();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

