#include "SceneLicensed.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "ServiceTextures.h"
#include "SceneCapcom.h"


SceneLicensed::SceneLicensed() : timer{3000}
{
	configSection = "Scene_Intro";
}


SceneLicensed::~SceneLicensed()
{
	configSection = nullptr;
}

bool SceneLicensed::Init()
{
	const fPoint& center = servicesManager->render->GetScreenCenter();

	texture = servicesManager->textures->Load(configSection);

	config->LoadSprite(licensed, configSection, "licensed");
	licensedPos.x = center.x;
	licensedPos.y = center.y;

	return true;
}

bool SceneLicensed::CleanUp()
{
	return true;
}

bool SceneLicensed::Start()
{
	Scene::Start();

	timer.Reset();
	return true;
}

Entity::Result SceneLicensed::UpdateState()
{
	if (timer.Reached() && !changing)
	{
		HandleSceneChange(new SceneCapcom());
	}
	return Entity::Result::R_OK;
}

Entity::Result SceneLicensed::Draw() const
{
	servicesManager->render->BlitGUI(texture, licensed.GetRectPosition(licensedPos), licensed.rect);
	return Entity::Result::R_OK;
}
