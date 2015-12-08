#include "Game.h"
#include "Defines.h"
#include "ModuleRender.h"

using namespace std;

Game::Game()
{
	modules.push_back(render = new ModuleRender());
}


Game::~Game()
{
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Game::Init()
{
	if (!config.Init())
	{
		LOG("Could not load config file");
		return false;
	}

	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(config); // we init everything, even if not anabled

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	//TODO: Load scene

	return ret;
}

Module::Update_result Game::Update()
{
	Module::Update_result ret = Module::Update_result::UPDATE_OK;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == Module::Update_result::UPDATE_OK; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == Module::Update_result::UPDATE_OK; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == Module::Update_result::UPDATE_OK; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();

	return ret;
}

bool Game::CleanUp()
{
	bool ret = true;

	for (list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	return ret;
}
