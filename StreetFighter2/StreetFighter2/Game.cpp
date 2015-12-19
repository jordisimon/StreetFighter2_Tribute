#include "Game.h"
#include "Config.h"
#include "ServicesManager.h"
#include "Defines.h"

#include "ServiceCommandManager.h"
#include "ServiceRender.h"

using namespace std;

Game::Game(): exit {false}
{
	config = new Config();
	servicesManager = new ServicesManager();
}


Game::~Game()
{
	RELEASE(servicesManager);
	RELEASE(config);
}

bool Game::Init()
{
	if (!config->Init())
	{
		LOG("Could not load config file");
		return false;
	}

	return servicesManager->Init();
}


bool Game::CleanUp()
{
	return servicesManager->CleanUp();
}

bool Game::UpdateInput()
{
	bool res = servicesManager->commands->UpdateInput();

	if (res)
		res = servicesManager->commands->ProcessInput();

	return res;
}

Entity::Result Game::PreDraw()
{
	if (servicesManager->render->ClearRender())
		return Entity::Result::R_OK;
	else
		return Entity::Result::R_ERROR;
}


Entity::Result Game::PostDraw()
{
	if (servicesManager->render->PresentRender())
		return Entity::Result::R_OK;
	else
		return Entity::Result::R_ERROR;
}

Entity::Result Game::Update()
{
	UpdateInput();

	if (exit)
		return Entity::Result::R_EXIT;

	Entity::Result ret = UpdateState();

	if (ret == Entity::Result::R_OK)
		ret = PreDraw();

	if (ret == Entity::Result::R_OK)
		ret = Draw();

	if (ret == Entity::Result::R_OK)
		ret = PostDraw();

	return ret;
}

Config* config = nullptr;
ServicesManager* servicesManager = nullptr;
