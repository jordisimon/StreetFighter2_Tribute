#include "Stage.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceAudio.h"
#include "ServiceCollition.h"
#include "Collider.h"
#include "ColliderType.h"
#include "Color.h"

bool Stage::Init()
{
	musicName = config->LoadCharValue(configSection, "music", "");

	config->LoadfPoint(camMin, configSection, "camMin");
	config->LoadfPoint(camMax, configSection, "camMax");
	config->LoadfPoint(camStart, configSection, "camStart");
	config->LoadfPoint(p1StartPoint, configSection, "p1Start");
	config->LoadfPoint(p2StartPoint, configSection, "p2Start");
	groundLevel = config->LoadIntValue(configSection, "groundLevel", "100");

	fRect box;
	config->LoadfRect(box, configSection, "colliderBox");
	boxCollider = servicesManager->collitions->CreateCollider(ColliderType::SCENE_BOX, box, nullptr, Color(Color::Predefined::BLUE));

	return true;
}

bool Stage::CleanUp()
{
	boxCollider->toDelete = true;
	return true;
}

bool Stage::Start()
{
	LOG("Starting stage");

	texture = servicesManager->textures->Load(configSection);

	return true;
}

bool Stage::Stop()
{
	LOG("Stopping stage");

	servicesManager->textures->Unload(texture);

	return true;
}
