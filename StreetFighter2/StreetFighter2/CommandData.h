#pragma once
#include <vector>

enum class CommandAction;  //To be defined in Game specific implementation
enum class CommandState;  //To be defined in Game specific implementation

struct CommandData
{
	std::vector<CommandAction> globalActions;
	std::vector<CommandState> globalStates;

	std::vector<CommandAction> p1Actions;
	std::vector<CommandState> p1States;

	std::vector<CommandAction> p2Actions;
	std::vector<CommandState> p2States;
};
