#pragma once
#include "Module.h"

class Config;

class ModuleCommandManager : public Module
{
private:
	bool debugEnabled;
	int debugCameraSpeed;

public:
	ModuleCommandManager() {};
	~ModuleCommandManager() {};

	bool Init(const Config& config);
	Module::Update_result Update();
};

