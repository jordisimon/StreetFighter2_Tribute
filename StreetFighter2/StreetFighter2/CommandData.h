#pragma once
#include <vector>

enum class CommandAction;  //To be defined in Game specific implementation
enum class CommandState;  //To be defined in Game specific implementation

struct CommandData
{
	std::vector<CommandAction> actions;
	std::vector<CommandState> states;
};
