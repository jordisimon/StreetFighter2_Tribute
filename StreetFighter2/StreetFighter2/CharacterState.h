#pragma once
#include "AttackInfo.h"
#include "CharacterSpecialAttack.h"
#include "Rect.h"

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
	virtual void Draw() const {};

	virtual void IfMovingForwardRecalculatePositionWithPressingSpeed() {};

	virtual const AttackInfo GetAttackInfo() const { return AttackInfo(); }

	virtual CharacterState* DoSpecialAction(const CharacterSpecialAttack& type) { return nullptr; }
	virtual CharacterState* DealHit(Collider* collider, const fRect& intersectionRect) { return nullptr; };
	virtual CharacterState* RoundFinished(int playerWin) { return nullptr; };
};

