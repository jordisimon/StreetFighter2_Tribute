#include "SceneLicensed.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "ServiceTextures.h"
#include "ServiceSceneManager.h"
#include "SceneCapcom.h"


SceneLicensed::SceneLicensed() : timer{3000}
{
	configSection = "Scene_Intro";
}


SceneLicensed::~SceneLicensed()
{
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
	//servicesManager->textures->Unload(texture);
	return true;
}

bool SceneLicensed::Start()
{
	Scene::Start();

	timer.Reset();
	changing = false;
	return true;
}

Entity::Result SceneLicensed::UpdateState()
{
	if (timer.Reached() && !changing)
	{
		servicesManager->scene->ChangeScene(new SceneCapcom());
		changing = true;
	}
	return Entity::Result::R_OK;
}

Entity::Result SceneLicensed::Draw() const
{
	servicesManager->render->BlitGUI(texture, licensed.GetRectPosition(licensedPos), licensed.rect);
	return Entity::Result::R_OK;
}
