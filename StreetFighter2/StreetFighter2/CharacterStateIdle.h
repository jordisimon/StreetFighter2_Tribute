#pragma once
#include "CharacterState.h"

class CharacterStateIdle :	public CharacterState
{
public:
	CharacterStateIdle(Character* p);
	~CharacterStateIdle();

	void OnEnter();
	void OnExit() {};

	State* ProcessInput(CommandData* commandData);
	//State* UpdateState() { return nullptr; };
};