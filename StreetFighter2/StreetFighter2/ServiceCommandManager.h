#pragma once
#include "Service.h"
#include <map>

class CommandContext;

class ServiceCommandManager : public Service
{
private:
	std::map<int, CommandContext*> commandContexts;
	CommandContext* currentCommandContext = nullptr;

	int debugCameraSpeed;

public:
	ServiceCommandManager() {};
	~ServiceCommandManager() {};

	bool Init();
	bool CleanUp();

	CommandContext* Load(const char* configSection);
	void Unload(const CommandContext* commandContext);
	void Unload(int id);
	
	void SetCurrentContext(CommandContext* context);
	bool UpdateInput();
	bool ProcessInput();
	bool ProcessInput(CommandContext* commandContext);

	//Special command
	bool CommandExit();
};

