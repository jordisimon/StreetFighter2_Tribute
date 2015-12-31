#pragma once
#include "RyuKenState.h"

class RyuKenStateHit : public RyuKenState
{
private:
	bool faceHit;
	float hitDuration;
	float moveBackwards;

public:
	RyuKenStateHit(RyuKen* p, bool face, float duration);
	~RyuKenStateHit();

	void OnEnter();
	void OnExit();

	CharacterState* UpdateState();
};

