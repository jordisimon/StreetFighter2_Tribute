#pragma once
#include "State.h"

class Player;

class PlayerState :	public State
{
protected:
	Player* player;
public:
	PlayerState(Player* p);
	~PlayerState();

	State* UpdateState();
};

