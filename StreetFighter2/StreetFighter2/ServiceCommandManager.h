#pragma once
#include "Service.h"
#include <map>

class CommandContext;

class ServiceCommandManager : public Service
{
private:
	std::map<int, CommandContext*> commandContexts;
	const CommandContext* currentCommandContext = nullptr;

	int debugCameraSpeed;

public:
	ServiceCommandManager() {};
	~ServiceCommandManager() {};

	bool Init();
	bool CleanUp();

	CommandContext* Load(const char* configSection);
	void Unload(const CommandContext* commandContext);
	void Unload(int id);
	
	void SetCurrentContext(const CommandContext* context);
	bool UpdateInput() const;
	bool ProcessInput() const;
	bool ProcessInput(const CommandContext* commandContext) const;

	//Special command
	bool CommandExit() const;
};

