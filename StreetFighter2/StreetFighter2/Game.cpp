#include "Game.h"
#include "Defines.h"
#include "ServiceRender.h"
#include "ServiceAudio.h"
#include "ServiceInput.h"
#include "ServiceTextures.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"

#include "ServiceCommandManager.h"

using namespace std;

Game::Game()
{
	SDL_Init(0);
	services.push_back(sRender = new ServiceRender());
	services.push_back(sTextures = new ServiceTextures());
	services.push_back(sParticles = new ServiceParticles());
	services.push_back(sCollitions = new ServiceCollition());
	services.push_back(sAudio = new ServiceAudio());
	services.push_back(sInput = new ServiceInput());

	//TODO treure d'aqui
	services.push_back(sCommands = new ServiceCommandManager());
}


Game::~Game()
{
	for (list<Service*>::iterator it = services.begin(); it != services.end(); ++it)
		RELEASE(*it);

	SDL_Quit();
}

bool Game::Init()
{
	if (!config.Init())
	{
		LOG("Could not load config file");
		return false;
	}

	debug = config.LoadBoolValue(DEBUG_SECTION, "enable", "0");

	bool ret = true;

	LOG("Init Services");

	for (list<Service*>::iterator it = services.begin(); it != services.end() && ret; ++it)
		ret = (*it)->Init(config);

	if (ret)
	{
		LOG("Start Services");

		for (list<Service*>::iterator it = services.begin(); it != services.end() && ret; ++it)
			ret = (*it)->Start();
	}

	return ret;
}


bool Game::CleanUp()
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

Entity::Result Game::ProcessInput()
{
	if (sInput->UpdateInput())
		return Entity::Result::R_OK;
	else
		return Entity::Result::R_ERROR;
}

Entity::Result Game::UpdateState()
{
	return Entity::Result::R_OK;
}

Entity::Result Game::PreDraw()
{
	if (sRender->ClearRender())
		return Entity::Result::R_OK;
	else
		return Entity::Result::R_ERROR;
}

Entity::Result Game::Draw()
{
	return Entity::Result::R_OK;
}

Entity::Result Game::PostDraw()
{
	if (sRender->PresentRender())
		return Entity::Result::R_OK;
	else
		return Entity::Result::R_ERROR;
}

Entity::Result Game::Update()
{
	Entity::Result ret = ProcessInput();

	if (ret == Entity::Result::R_OK)
		ret = UpdateState();

	if (ret == Entity::Result::R_OK)
		ret = PreDraw();

	if (ret == Entity::Result::R_OK)
		ret = Draw();

	if (ret == Entity::Result::R_OK)
		ret = PostDraw();

	return ret;
}
