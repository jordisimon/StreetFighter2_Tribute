#pragma once
#include "Game.h"

class CommandContext;
class Scene;

//Testing
class ServiceCommandManager;
class SceneMatch;
class ParticleFactory;

class SF2Game :	public Game
{
private:
	//Debug
	bool debug;
	float debugCameraSpeed;
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

	bool UpdateInput() const;
	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

