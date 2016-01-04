#pragma once
#include "RyuKenState.h"

class RyuKenStateBlocking :	public RyuKenState
{
protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);
	CharacterState* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateBlocking(RyuKen* p);
	~RyuKenStateBlocking();

	void OnEnter();

	CharacterState* UpdateState();

	CharacterState* DoSpecialAction(const CharacterSpecialAttack& type);
	CharacterState* DealHit(Collider* collider);
};

