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

	CharacterState* ManageHitImpacted(const AttackInfo& attackInfo, const fRect& intersectionRect, bool enemyHit, bool faceHit, bool crouching);
	CharacterState* ManageHitBlocked(const AttackInfo& attackInfo, const fRect& intersectionRect, bool enemyHit);

public:
	RyuKenState(RyuKen* p);
	~RyuKenState();

	void OnEnter();
	void OnExit();

	CharacterState* ProcessInput(CommandData* commandData);
	CharacterState* UpdateState();

	CharacterState* DealHit(Collider* collider, const fRect& intersectionRect);
	CharacterState* RoundFinished(int playerWin);
};

