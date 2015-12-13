#include "ServiceCommandManager.h"
#include "Defines.h"
#include "Config.h"
#include "Game.h"
#include "ServiceInput.h"
#include "ServiceRender.h"
#include "SDL\include\SDL_scancode.h"

bool ServiceCommandManager::Init(const Config & config)
{
	LOG("Init Command Manager Service");
	debugCameraSpeed = config.LoadIntValue(DEBUG_SECTION, "debugCameraSpeed", "3");

	return true;
}

bool ServiceCommandManager::Update()
{
	//Debug keys
	if (game->debug)
	{
		if (game->sInput->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_REPEAT)
			game->sRender->MoveCamera(iPoint( 0, debugCameraSpeed ));

		if (game->sInput->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_REPEAT)
			game->sRender->MoveCamera(iPoint( 0, -debugCameraSpeed ));

		if (game->sInput->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT)
			game->sRender->MoveCamera(iPoint( debugCameraSpeed, 0 ));

		if (game->sInput->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT)
			game->sRender->MoveCamera(iPoint( -debugCameraSpeed, 0 ));
	}

	return true;
}

bool ServiceCommandManager::CommandExit()
{
	return (game->sInput->GetWindowEvent(EventWindow::WE_QUIT)
		|| game->sInput->GetKey(SDL_SCANCODE_ESCAPE) == KeyState::KEY_DOWN);
}

bool ServiceCommandManager::P1Left()
{
	return game->sInput->GetKey(SDL_SCANCODE_A) == KeyState::KEY_DOWN
		|| game->sInput->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT;
}

bool ServiceCommandManager::P1Right()
{
	return game->sInput->GetKey(SDL_SCANCODE_D) == KeyState::KEY_DOWN
		|| game->sInput->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT;
}

bool ServiceCommandManager::P1Up()
{
	return game->sInput->GetKey(SDL_SCANCODE_W) == KeyState::KEY_DOWN
		|| game->sInput->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT;
}

bool ServiceCommandManager::P1Down()
{
	return game->sInput->GetKey(SDL_SCANCODE_S) == KeyState::KEY_DOWN
		|| game->sInput->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT;
}

bool ServiceCommandManager::P1UpLeft()
{
	return P1Up() && P1Left();
}

bool ServiceCommandManager::P1UpRight()
{
	return P1Up() && P1Right();
}

bool ServiceCommandManager::P1DownLeft()
{
	return P1Down() && P1Left();
}

bool ServiceCommandManager::P1DownRight()
{
	return P1Down() && P1Right();
}

bool ServiceCommandManager::P1LPunch()
{
	return game->sInput->GetKey(SDL_SCANCODE_U) == KeyState::KEY_DOWN;
}
