#pragma once
#include <map>
#include <vector>
//#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL_scancode.h"

enum class GameControllerButton;
enum class CommandAction;
enum class CommandState;
struct CommandData;
class Entity;
class Config;

class CommandContext
{
private:
	const char* contextName;

	std::map<GameControllerButton, CommandAction> controller1ActionMap;
	std::map<GameControllerButton, CommandState> controller1StateMap;
	std::map<GameControllerButton, CommandAction> controller2ActionMap;
	std::map<GameControllerButton, CommandState> controller2StateMap;
	std::map<SDL_Scancode, CommandAction> keyGlobalActionMap;
	std::map<SDL_Scancode, CommandState> keyGlobalStateMap;
	std::map<SDL_Scancode, CommandAction> key1ActionMap;
	std::map<SDL_Scancode, CommandState> key1StateMap;
	std::map<SDL_Scancode, CommandAction> key2ActionMap;
	std::map<SDL_Scancode, CommandState> key2StateMap;

	std::vector<Entity*> commandListeners;

	bool FillCommandData(CommandData* commandData) const;
	bool DispatchCommandData(CommandData* commandData) const;

public:
	CommandContext(const char* name);
	virtual ~CommandContext();

	bool Init();

	void AddCommandListener(Entity* listener);
	void RemoveCommandListener(Entity* listener);

	bool ProcessInput() const;
};

