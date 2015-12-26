#pragma once
#include <list>
#include "Config.h"

class Service;
class ServiceAudio;
class ServiceInput;
class ServiceCommandManager;
class ServiceParticles;
class ServiceRender;
class ServiceTextures;
class ServiceCollition;
class ServiceTime;

class ServicesManager
{
private:
	std::list<Service*> services;

public:
	bool debug;

	//Services
	ServiceAudio* audio = nullptr;
	ServiceInput* input = nullptr;
	ServiceCommandManager* commands = nullptr;
	ServiceRender* render = nullptr;
	ServiceParticles* particles = nullptr;
	ServiceCollition* collitions = nullptr;
	ServiceTextures* textures = nullptr;
	ServiceTime* time = nullptr;

	ServicesManager();
	~ServicesManager();

	bool Init();
	bool CleanUp();
};

extern ServicesManager* servicesManager;

