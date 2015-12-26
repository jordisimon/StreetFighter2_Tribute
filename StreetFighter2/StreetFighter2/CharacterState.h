#pragma once
#include "State.h"

class CharacterState :	public State
{
public:
	CharacterState();
	~CharacterState();

	State* ProcessInput(CommandData* commandData);
};

