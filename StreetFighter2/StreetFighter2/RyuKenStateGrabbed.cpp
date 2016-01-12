#include "RyuKenStateGrabbed.h"
#include "RyuKen.h"



RyuKenStateGrabbed::RyuKenStateGrabbed(RyuKen* p, Direction dir) : RyuKenState{ p }, direction{ dir }
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

void RyuKenStateGrabbed::Draw() const
{
	character->DrawDefault(direction);
}
