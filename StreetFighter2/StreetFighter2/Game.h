#pragma once
#include <list>
#include "Config.h"
#include "Module.h"

class ModuleRender;

class Game
{
private:
	std::list<Module*> modules;

public:
	Config config;
	ModuleRender* render;

	Game();
	~Game();

	bool Init();
	Module::Update_result Update();
	bool CleanUp();
};

