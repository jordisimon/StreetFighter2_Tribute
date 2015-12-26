#include "ServicesManager.h"
#include "Defines.h"
#include "Service.h"
#include "ServiceRender.h"
#include "ServiceAudio.h"
#include "ServiceInput.h"
#include "ServiceCommandManager.h"
#include "ServiceTextures.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"
#include "ServiceTime.h"
#include "Config.h"

using namespace std;

ServicesManager::ServicesManager()
{
	SDL_Init(0);
	services.push_back(render = new ServiceRender());
	services.push_back(textures = new ServiceTextures());
	services.push_back(commands = new ServiceCommandManager());
	services.push_back(particles = new ServiceParticles());
	services.push_back(collitions = new ServiceCollition());
	services.push_back(audio = new ServiceAudio());
	services.push_back(input = new ServiceInput());
	services.push_back(time = new ServiceTime());
}


ServicesManager::~ServicesManager()
{
	for (list<Service*>::iterator it = services.begin(); it != services.end(); ++it)
		RELEASE(*it);

	SDL_Quit();
}

bool ServicesManager::Init()
{
	debug = config->LoadBoolValue(DEBUG_SECTION, "enable", "0");

	bool ret = true;

	LOG("Init Services");

	for (list<Service*>::iterator it = services.begin(); it != services.end() && ret; ++it)
		ret = (*it)->Init();

	if (ret)
	{
		LOG("Start Services");

		for (list<Service*>::iterator it = services.begin(); it != services.end() && ret; ++it)
			ret = (*it)->Start();
	}

	return ret;
}

bool ServicesManager::CleanUp()
{
	bool ret = true;

	LOG("Stop Services");
	for (list<Service*>::iterator it = services.begin(); it != services.end(); ++it)
		ret = ret && (*it)->Stop();

	LOG("CleanUp Services");
	for (list<Service*>::iterator it = services.begin(); it != services.end(); ++it)
		ret = ret && (*it)->CleanUp();

	return ret;
}
