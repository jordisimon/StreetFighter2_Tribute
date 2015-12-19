#pragma once
#include "State.h"

class Character;

class CharacterState :	public State
{
protected:
	Character* character = nullptr;

public:
	CharacterState(Character* p);
	~CharacterState();

	State* UpdateState();
};

