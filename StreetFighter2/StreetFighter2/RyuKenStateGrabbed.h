#pragma once
#include "RyuKenState.h"
#include "Direction.h"

//In this state, character will act as a puppet, animation and position changes will be managed by rival
class RyuKenStateGrabbed : public RyuKenState
{
public:
	RyuKenStateGrabbed(RyuKen* p, Direction dir);
	~RyuKenStateGrabbed();

	void OnEnter();
	void OnExit();

	CharacterState* ProcessInput(CommandData* commandData);
	CharacterState* UpdateState();
};

