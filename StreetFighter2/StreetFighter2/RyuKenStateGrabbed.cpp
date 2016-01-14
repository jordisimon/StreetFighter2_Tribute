#include "RyuKenStateGrabbed.h"
#include "RyuKen.h"



RyuKenStateGrabbed::RyuKenStateGrabbed(RyuKen* p, Direction dir) : RyuKenState{ p, false }
{
}


RyuKenStateGrabbed::~RyuKenStateGrabbed()
{
}

void RyuKenStateGrabbed::OnEnter()
{
	character->isGrabbed = true;
}

void RyuKenStateGrabbed::OnExit()
{
	character->isGrabbed = false;
}

CharacterState * RyuKenStateGrabbed::ProcessInput(CommandData * commandData)
{
	return nullptr;
}

CharacterState * RyuKenStateGrabbed::UpdateState()
{
	return nullptr;
}
