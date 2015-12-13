#pragma once
#include "PlayerState.h"
class PlayerStateFWalk : public PlayerState
{
public:
	PlayerStateFWalk(Player* p);
	~PlayerStateFWalk();

	void OnEnter();
};

