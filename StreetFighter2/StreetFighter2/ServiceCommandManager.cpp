#include "ServiceCommandManager.h"
#include "Defines.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceInput.h"
#include "CommandContext.h"


#include "ServiceRender.h"
#include "SDL\include\SDL_scancode.h"

using namespace std;

bool ServiceCommandManager::Init()
{
	LOG("Init Command Manager Service");
	debugCameraSpeed = config->LoadIntValue(DEBUG_SECTION, "debugCameraSpeed", "3");

	return true;
}

bool ServiceCommandManager::CleanUp()
{
	LOG("CleanUp Command Manager Service");

	for (map<int, CommandContext*>::iterator it = commandContexts.begin(); it != commandContexts.end(); ++it)
		RELEASE(it->second);

	commandContexts.clear();

	return true;
}

CommandContext * ServiceCommandManager::Load(const char * configSection)
{
	//Find command context id
	int commandContextId = config->LoadIntValue(configSection, "commandContextId", "-1");

	if (commandContextId == -1)
		return nullptr;

	//If texture already loaded, return it
	map<int, CommandContext*>::const_iterator it = commandContexts.find(commandContextId);
	if (it != commandContexts.cend())
	{
		return it->second;
	}

	//If not loaded, create, load and store
	CommandContext* commandContext = new CommandContext(configSection);
	commandContext->Init();
	commandContexts[commandContextId] = commandContext;
	return commandContext;
}

void ServiceCommandManager::Unload(const CommandContext * commandContext)
{
	for (map<int, CommandContext*>::iterator it = commandContexts.begin(); it != commandContexts.end(); ++it)
	{
		if (it->second == commandContext)
		{
			RELEASE(it->second);
			commandContexts.erase(it);
			break;
		}
	}
}

void ServiceCommandManager::Unload(int id)
{
	map<int, CommandContext*>::iterator it = commandContexts.find(id);
	if (it != commandContexts.cend())
	{
		RELEASE(it->second);
		commandContexts.erase(it);
	}
}


bool ServiceCommandManager::UpdateInput()
{
	return servicesManager->input->UpdateInput();
}

bool ServiceCommandManager::ProcessInput()
{
	if (currentCommandContext != nullptr)
		return currentCommandContext->ProcessInput();

	return true;
}

bool ServiceCommandManager::ProcessInput(CommandContext * commandContext)
{
	if (commandContext != nullptr)
		return commandContext->ProcessInput();

	return true;
}


void ServiceCommandManager::SetCurrentContext(CommandContext * context)
{
	currentCommandContext = context;
}

bool ServiceCommandManager::CommandExit()
{
	return (servicesManager->input->GetWindowEvent(EventWindow::WE_QUIT)
		|| servicesManager->input->GetKey(SDL_SCANCODE_ESCAPE) == KeyState::KEY_DOWN);
}
