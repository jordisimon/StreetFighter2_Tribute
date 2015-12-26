#include "CommandContext.h"
#include <cstdlib>
#include "Defines.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceInput.h"
#include "Entity.h"
#include "CommandData.h"


using namespace std;

CommandContext::CommandContext(const char* name): contextName { name }
{
}

CommandContext::~CommandContext()
{
}

bool CommandContext::Init()
{
	int commandNum = 0;
	char* commandNumChar = new char[3];

	char* auxKey = new char[100]; //should be enough for all keys in config file
	char* result = new char[100];

	int controllerNumber;
	GameControllerButton controllerButton;
	SDL_Scancode keyboardCode;
	CommandAction action;
	CommandState state;

	bool commandFound;
	//Actions
	do
	{
		sprintf(commandNumChar, "%d", commandNum);

		strcpy(auxKey, "action"); strcat(auxKey, commandNumChar);
		strcpy(result, config->LoadCharValue(contextName, auxKey, "-1,-1,-1,-1"));

		controllerNumber = atoi(strtok(result, ","));

		commandFound = (controllerNumber != -1);

		if (commandFound)
		{
			controllerButton = (GameControllerButton)atoi(strtok(NULL, ","));
			keyboardCode = (SDL_Scancode)atoi(strtok(NULL, ","));
			action = (CommandAction)atoi(strtok(NULL, ","));;

			switch (controllerNumber)
			{
			case 0: //No controller, only keyboard
				keyGlobalActionMap.insert(pair<SDL_Scancode, CommandAction>(keyboardCode, action));
				break;
			case 1:
				controller1ActionMap.insert(pair<GameControllerButton, CommandAction>(controllerButton, action));
				key1ActionMap.insert(pair<SDL_Scancode, CommandAction>(keyboardCode, action));
				break;
			case 2:
				controller2ActionMap.insert(pair<GameControllerButton, CommandAction>(controllerButton, action));
				key2ActionMap.insert(pair<SDL_Scancode, CommandAction>(keyboardCode, action));
				break;
			}
		}

		commandNum++;
	} while (commandFound);

	//States
	commandNum = 0;
	do
	{
		sprintf(commandNumChar, "%d", commandNum);

		strcpy(auxKey, "state"); strcat(auxKey, commandNumChar);
		strcpy(result, config->LoadCharValue(contextName, auxKey, "-1,-1,-1,-1"));

		controllerNumber = atoi(strtok(result, ","));

		commandFound = (controllerNumber != -1);

		if (commandFound)
		{
			controllerButton = (GameControllerButton)atoi(strtok(NULL, ","));
			keyboardCode = (SDL_Scancode)atoi(strtok(NULL, ","));
			state = (CommandState)atoi(strtok(NULL, ","));;

			switch (controllerNumber)
			{
			case 0: //No controller, only keyboard
				keyGlobalStateMap.insert(pair<SDL_Scancode, CommandState>(keyboardCode, state));
				break;
			case 1:
				controller1StateMap.insert(pair<GameControllerButton, CommandState>(controllerButton, state));
				key1StateMap.insert(pair<SDL_Scancode, CommandState>(keyboardCode, state));
				break;
			case 2:
				controller2StateMap.insert(pair<GameControllerButton, CommandState>(controllerButton, state));
				key2StateMap.insert(pair<SDL_Scancode, CommandState>(keyboardCode, state));
				break;
			}		
		}

		commandNum++;
	} while (commandFound);

	RELEASE_ARRAY(result);
	RELEASE_ARRAY(auxKey);
	RELEASE_ARRAY(commandNumChar);
	return true;
}


void CommandContext::AddCommandListener(Entity * listener)
{
	bool found = false;

	for (vector<Entity*>::const_iterator it = commandListeners.cbegin(); it < commandListeners.cend(); ++it)
	{
		if ((*it) == listener)
		{
			found = true;
			break;
		}
	}

	if (!found)
		commandListeners.push_back(listener);
}

void CommandContext::RemoveCommandListener(Entity * listener)
{
	for (vector<Entity*>::iterator it = commandListeners.begin(); it < commandListeners.end(); ++it)
	{
		if ((*it) == listener)
		{
			commandListeners.erase(it);
			break;
		}
	}
}


bool CommandContext::FillCommandData(CommandData* commandData)
{
	//Global keys
	//Actions
	for (auto const& command : keyGlobalActionMap)
	{
		if (servicesManager->input->GetKey(command.first) == KeyState::KEY_DOWN)
			commandData->globalActions.push_back(command.second);
	}

	//States
	for (auto const& command : keyGlobalStateMap)
	{
		if (servicesManager->input->GetKey(command.first) == KeyState::KEY_DOWN ||
			servicesManager->input->GetKey(command.first) == KeyState::KEY_REPEAT)
			commandData->globalStates.push_back(command.second);
	}

	//Player 1
	if (servicesManager->input->ExistController(1))
	{
		//Actions
		for (auto const& command : controller1ActionMap)
		{
			if (servicesManager->input->GetControllerButton(1, (int)command.first) == KeyState::KEY_DOWN)
				commandData->p1Actions.push_back(command.second);
		}

		//States
		for (auto const& command : controller1StateMap)
		{
			if (servicesManager->input->GetControllerButton(1, (int)command.first) == KeyState::KEY_DOWN ||
				servicesManager->input->GetControllerButton(1, (int)command.first) == KeyState::KEY_REPEAT)
				commandData->p1States.push_back(command.second);
		}
	}
	else
	{
		//Actions
		for (auto const& command : key1ActionMap)
		{
			if (servicesManager->input->GetKey(command.first) == KeyState::KEY_DOWN)
				commandData->p1Actions.push_back(command.second);
		}

		//States
		for (auto const& command : key1StateMap)
		{
			if (servicesManager->input->GetKey(command.first) == KeyState::KEY_DOWN ||
				servicesManager->input->GetKey(command.first) == KeyState::KEY_REPEAT)
				commandData->p1States.push_back(command.second);
		}
	}

	//Player 2
	if (servicesManager->input->ExistController(2))
	{
		//Actions
		for (auto const& command : controller2ActionMap)
		{
			if (servicesManager->input->GetControllerButton(2, (int)command.first) == KeyState::KEY_DOWN)
				commandData->p2Actions.push_back(command.second);
		}

		//States
		for (auto const& command : controller2StateMap)
		{
			if (servicesManager->input->GetControllerButton(2, (int)command.first) == KeyState::KEY_DOWN ||
				servicesManager->input->GetControllerButton(2, (int)command.first) == KeyState::KEY_REPEAT)
				commandData->p2States.push_back(command.second);
		}
	}
	else
	{
		//Actions
		for (auto const& command : key2ActionMap)
		{
			if (servicesManager->input->GetKey(command.first) == KeyState::KEY_DOWN)
				commandData->p2Actions.push_back(command.second);
		}

		//States
		for (auto const& command : key2StateMap)
		{
			if (servicesManager->input->GetKey(command.first) == KeyState::KEY_DOWN ||
				servicesManager->input->GetKey(command.first) == KeyState::KEY_REPEAT)
				commandData->p2States.push_back(command.second);
		}
	}

	return true;
}

bool CommandContext::DispatchCommandData(CommandData* commandData)
{
	for (vector<Entity*>::const_iterator it = commandListeners.cbegin(); it != commandListeners.cend(); ++it)
	{
		(*it)->ProcessInput(commandData);
	}
	return true;
}

bool CommandContext::ProcessInput()
{
	CommandData commandData;

	bool res = FillCommandData(&commandData);

	if (res)
		res = DispatchCommandData(&commandData);

	return res;
}
