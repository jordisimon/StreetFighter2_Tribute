#pragma once
#include "CharacterState.h"
class CharacterStateFWalk : public CharacterState
{
public:
	CharacterStateFWalk(Character* p);
	~CharacterStateFWalk();

	void OnEnter();
};

