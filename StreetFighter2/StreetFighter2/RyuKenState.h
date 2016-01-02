#pragma once
#include "CharacterState.h"
#include <vector>
#include "CommandAction.h"
#include "CommandState.h"

class RyuKen;

class RyuKenState :	public CharacterState
{
protected:
	RyuKen* character = nullptr;

	virtual CharacterState* ProcessActions(std::vector<CommandAction> actions) { return nullptr; };
	virtual CharacterState* ProcessStates(std::vector<CommandState> states) { return nullptr; };

public:
	RyuKenState(RyuKen* p);
	~RyuKenState();

	void OnEnter();
	void OnExit();

	CharacterState* ProcessInput(CommandData* commandData);
	CharacterState* UpdateState();

	CharacterState* DealHit(Collider* collider);
	CharacterState* MatchFinished(int playerWin);
};

