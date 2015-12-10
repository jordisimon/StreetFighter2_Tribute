#include "ModuleCommandManager.h"
#include "Defines.h"
#include "Config.h"
#include "Game.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL\include\SDL_scancode.h"

#define CONFIG_SECTION "Debug"

bool ModuleCommandManager::Init(const Config & config)
{
	LOG("Init Command Manager");
	debugCameraSpeed = config.LoadIntValue(CONFIG_SECTION, "debugCameraSpeed", "3");

	return true;
}

Module::Update_result ModuleCommandManager::Update()
{
	//Debug keys
	if (game->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_REPEAT)
		game->render->MoveCamera({0, debugCameraSpeed });

	if (game->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_REPEAT)
		game->render->MoveCamera({ 0, -debugCameraSpeed });

	if (game->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT)
		game->render->MoveCamera({ debugCameraSpeed, 0 });

	if (game->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT)
		game->render->MoveCamera({ -debugCameraSpeed, 0 });

	return Module::Update_result::UPDATE_OK;
}
