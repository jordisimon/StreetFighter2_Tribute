#pragma once
#include <list>
#include "Config.h"
#include "Module.h"

class ModuleInput;
class ModuleRender;
class ModuleTextures;
class ModuleAudio;
class ModuleCommandManager;

class StageHonda;

class Game
{
private:
	std::list<Module*> modules;

public:
	Config config;
	ModuleInput* input;
	ModuleRender* render;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleCommandManager* commandManager;


	//Testing
	StageHonda* sHonda;

	Game();
	~Game();

	bool Init();
	Module::Update_result Update();
	bool CleanUp();
};

extern Game* game;

