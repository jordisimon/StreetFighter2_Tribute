#pragma once
#include "CharacterState.h"

class CharacterStateJump : public CharacterState
{
public:
	CharacterStateJump(Character* p);
	~CharacterStateJump();

	void OnEnter();
	void OnExit() {};

	State* ProcessInput(CommandData* commandData);
};

