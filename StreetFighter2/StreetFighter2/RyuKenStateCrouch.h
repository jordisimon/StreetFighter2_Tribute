#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateCrouch : public RyuKenState
{
private: 
	bool defending;
	bool blocking;

protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);
	CharacterState* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateCrouch(RyuKen* p, bool def);
	~RyuKenStateCrouch();

	void OnEnter();

	CharacterState* UpdateState();

	CharacterState* DoSpecialAction(const CharacterSpecialAttack& type);
	CharacterState* DealHit(Collider* collider, const fRect& intersectionRect);
};

