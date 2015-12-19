#pragma once
#include "Game.h"

class CommandContext;
class Scene;

//Testing
class ServiceCommandManager;
class SceneMatch;

class SF2Game :	public Game
{
private:
	//Debug
	bool debug;
	int debugCameraSpeed;
	CommandContext* debugCommandContext;

	Scene* currentScene;

	//Testing 
	//SceneMatch* match = nullptr;
	//ServiceCommandManager* sCommands = nullptr;

public:
	SF2Game();
	~SF2Game();

	bool Init();
	bool CleanUp();

	bool UpdateInput();
	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();
	Entity::Result Draw();
};

