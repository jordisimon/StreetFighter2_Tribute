#include "RyuKenState.h"
#include "RyuKen.h"
#include "CommandData.h"


RyuKenState::RyuKenState(RyuKen* p) : character{ p }
{
}


RyuKenState::~RyuKenState()
{
}

State * RyuKenState::ProcessInput(CommandData * commandData)
{
	//Default behaviour
	State* result = nullptr;

	if (character->playerNumber == 1)
	{
		result = ProcessActions(commandData->p1Actions);
		if (result == nullptr)
			result = ProcessStates(commandData->p1States);
	}
	else
	{
		result = ProcessActions(commandData->p2Actions);
		if (result == nullptr)
			result = ProcessStates(commandData->p2States);
	}

	return result;
}
