#include "SceneCapcom.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "ServiceTextures.h"
#include "ServiceAudio.h"
#include "SceneMainMenu.h"


SceneCapcom::SceneCapcom() : timer{ 2000 }
{
	configSection = "Scene_Intro";
}


SceneCapcom::~SceneCapcom()
{
	configSection = nullptr;
}


bool SceneCapcom::Init()
{
	const fPoint& center = servicesManager->render->GetScreenCenter();

	texture = servicesManager->textures->Load(configSection);

	config->LoadAnimation(capcom, configSection, "capcom");
	capcomPos.x = center.x;
	capcomPos.y = center.y;

	capcomSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Music\\Capcom.ogg");

	return true;
}

bool SceneCapcom::CleanUp()
{
	return true;
}

bool SceneCapcom::Start()
{
	Scene::Start();

	capcom.ResetAnimation();
	step = 0;
	timer.SetNewInterval(2000);
	servicesManager->audio->PlayFx(capcomSfx);
	return true;
}

Entity::Result SceneCapcom::UpdateState()
{
	switch (step)
	{
	case 0:
		if (timer.Reached())
		{
			step++;
			timer.SetNewInterval(1000);
		}
		break;

	case 1:
		capcom.UpdateCurrentFrame();
		if (timer.Reached() && !changing)
		{
			HandleSceneChange(new SceneMainMenu());
		}
		break;

	}
	return Entity::Result::R_OK;
}

Entity::Result SceneCapcom::Draw() const
{
	servicesManager->render->BlitGUI(texture, capcom.GetFrame().GetRectPosition(capcomPos), capcom.GetFrame().rect);
	return Entity::Result::R_OK;
}
