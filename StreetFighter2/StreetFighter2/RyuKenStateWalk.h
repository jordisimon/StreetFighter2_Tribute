#pragma once
#include "RyuKenState.h"
#include "Direction.h"

class RyuKenStateWalk :	public RyuKenState
{
private:
	bool forward;

protected:
	CharacterState* ProcessActions(std::vector<CommandAction> actions);
	CharacterState* ProcessStates(std::vector<CommandState> states);

public:
	RyuKenStateWalk(RyuKen* p, Direction direction);
	RyuKenStateWalk(RyuKen* p, bool f);
	~RyuKenStateWalk();

	void OnEnter();

	CharacterState* UpdateState();

	CharacterState* DoSpecialAction(const CharacterSpecialAttack& type);
	void IfMovingForwardRecalculatePositionWithPressingSpeed();
};

