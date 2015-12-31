#pragma once
#include "RyuKenState.h"

class RyuKenStateJump :	public RyuKenState
{
private:
	float jumpSpeed;
public:
	RyuKenStateJump(RyuKen* p);
	~RyuKenStateJump();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

