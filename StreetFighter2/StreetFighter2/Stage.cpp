#include "Stage.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"

bool Stage::Init()
{
	texture = servicesManager->textures->Load(configSection);
	musicName = config->LoadCharValue(configSection, "music", "");

	config->LoadfPoint(camMin, configSection, "camMin");
	config->LoadfPoint(camMax, configSection, "camMax");
	config->LoadfPoint(camStart, configSection, "camStart");
	config->LoadfPoint(p1StartPoint, configSection, "p1Start");
	config->LoadfPoint(p2StartPoint, configSection, "p2Start");
	groundLevel = config->LoadIntValue(configSection, "groundLevel", "100");

	return true;
}

bool Stage::CleanUp()
{
	servicesManager->textures->Unload(texture);
	return true;
}

bool Stage::Start()
{
	showFinishAnimations = false;

	return true;
}
