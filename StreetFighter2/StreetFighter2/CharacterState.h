#pragma once
#include "AttackInfo.h"
#include "CharacterSpecialAttack.h"

struct CommandData;
class Collider;

class CharacterState
{
public:
	CharacterState();
	virtual ~CharacterState();

	virtual void OnEnter() {};
	virtual void OnExit() {};

	virtual CharacterState* ProcessInput(CommandData* commandData) { return nullptr; };
	virtual CharacterState* UpdateState() { return nullptr; };

	virtual void IfMovingForwardRecalculatePositionWithPressingSpeed() {};

	virtual AttackInfo GetAttackInfo() { return AttackInfo(); }

	virtual CharacterState* DoSpecialAction(const CharacterSpecialAttack& type) { return nullptr; }
	virtual CharacterState* DealHit(Collider* collider) { return nullptr; };
	virtual CharacterState* MatchFinished(int playerWin) { return nullptr; };
};

