#include "Stage.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceAudio.h"
#include "ServiceCollition.h"
#include "Collider.h"
#include "ColliderType.h"
#include "Color.h"
#include "SDL\include\SDL_rect.h"


bool Stage::Init()
{
	musicName = config->LoadCharValue(configSection, "music", "");

	config->LoadPoint(camMin, configSection, "camMin");
	config->LoadPoint(camMax, configSection, "camMax");
	config->LoadPoint(camStart, configSection, "camStart");
	config->LoadPoint(p1StartPoint, configSection, "p1Start");
	config->LoadPoint(p2StartPoint, configSection, "p2Start");
	groundLevel = config->LoadIntValue(configSection, "groundLevel", "100");

	SDL_Rect box;
	config->LoadSDLRect(box, configSection, "colliderBox");
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
