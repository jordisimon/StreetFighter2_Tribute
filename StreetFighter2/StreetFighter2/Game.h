#pragma once
#include "Entity.h"
#include <list>
#include "Config.h"
#include "Service.h"

class ServiceAudio;
class ServiceInput;
class ServiceParticles;
class ServiceRender;
class ServiceTextures;
class ServiceCollition;

//TODO treure d'aqui
class ServiceCommandManager;

class Game: public Entity
{
private:
	std::list<Service*> services;

public:
	Config config;
	bool debug;

	//Services
	ServiceAudio* sAudio;
	ServiceInput* sInput;
	ServiceRender* sRender;
	ServiceParticles* sParticles;
	ServiceCollition* sCollitions;
	ServiceTextures* sTextures;

	//TODO treure d'aqui
	ServiceCommandManager* sCommands;

	Game();
	~Game();

	virtual bool Init();
	bool CleanUp();

	Entity::Result ProcessInput();
	Entity::Result UpdateState();
	Entity::Result PreDraw();
	Entity::Result Draw();
	Entity::Result PostDraw();

	Entity::Result Update();
};

Game* CreateGame();

extern Game* game;

