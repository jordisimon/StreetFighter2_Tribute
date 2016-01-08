#pragma once
#include "RyuKenState.h"
#include "AttackInfo.h"

class RyuKenStateHit : public RyuKenState
{
private:
	bool crouching;
	bool faceHit;
	AttackStrength strength;
	float moveBackwards;

public:
	RyuKenStateHit(RyuKen* p, bool crouch, bool face, AttackStrength str);
	~RyuKenStateHit();

	void OnEnter();

	CharacterState* UpdateState();
};

