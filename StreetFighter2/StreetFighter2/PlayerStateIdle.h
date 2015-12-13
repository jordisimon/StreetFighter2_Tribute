#pragma once
#include "PlayerState.h"

class PlayerStateIdle :	public PlayerState
{
public:
	PlayerStateIdle(Player* p);
	~PlayerStateIdle();

	void OnEnter();
	virtual void OnExit() {};

	//virtual State* ProcessInput() { return nullptr; };
	//virtual State* UpdateState() { return nullptr; };
};

