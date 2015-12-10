#include "Stage.h"
#include "Defines.h"
#include "Game.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


bool Stage::Start()
{
	LOG("Starting scene");

	graphics = game->textures->Load(spriteSheetName);

	//game->player->Enable();
	game->audio->PlayMusic(musicName);

	return true;
}

bool Stage::Stop()
{
	LOG("Stopping scene");

	game->textures->Unload(graphics);
	//game->player->Disable();

	return true;
}
