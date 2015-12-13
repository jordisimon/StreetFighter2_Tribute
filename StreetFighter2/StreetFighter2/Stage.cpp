#include "Stage.h"
#include "Defines.h"
#include "Game.h"
#include "ServiceTextures.h"
#include "ServiceAudio.h"


bool Stage::Init(const Config & config)
{
	musicName = config.LoadCharValue(configSection, "music", "");

	config.LoadPoint(camMin, configSection, "camMin");
	config.LoadPoint(camMax, configSection, "camMax");
	config.LoadPoint(camStart, configSection, "camStart");
	config.LoadPoint(p1StartPoint, configSection, "p1Start");
	config.LoadPoint(p2StartPoint, configSection, "p2Start");
	groundLevel = config.LoadIntValue(configSection, "groundLevel", "100");

	return true;
}

bool Stage::Start()
{
	LOG("Starting stage");

	texture = game->sTextures->Load(configSection);

	//game->sAudio->PlayMusic(musicName);

	return true;
}

bool Stage::Stop()
{
	LOG("Stopping stage");

	game->sTextures->Unload(texture);

	return true;
}
