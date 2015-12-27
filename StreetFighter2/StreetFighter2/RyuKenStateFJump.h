#pragma once
#include "RyuKenState.h"

class RyuKenStateFJump : public RyuKenState
{
private:
	float jumpSpeed;
public:
	RyuKenStateFJump(RyuKen* p);
	~RyuKenStateFJump();

	void OnEnter();
	void OnExit();

	State* UpdateState();
};

