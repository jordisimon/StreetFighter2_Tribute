#pragma once
#include "RyuKenState.h"

class RyuKenStateHit : public RyuKenState
{
private:
	bool crouching;
	bool faceHit;
	float hitDuration;
	float moveBackwards;

public:
	RyuKenStateHit(RyuKen* p, bool crouch, bool face, float duration);
	~RyuKenStateHit();

	void OnEnter();

	CharacterState* UpdateState();
};

