#include "SceneCapcom.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "ServiceTextures.h"
#include "ServiceAudio.h"
#include "ServiceSceneManager.h"
#include "SceneMainMenu.h"

//Testing
#include "SceneMatch.h"
#include "SceneMatchInfo.h"


SceneCapcom::SceneCapcom() : timer{ 2000 }
{
	configSection = "Scene_Intro";
}


SceneCapcom::~SceneCapcom()
{
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
	//servicesManager->textures->Unload(texture);
	return true;
}

bool SceneCapcom::Start()
{
	Scene::Start();

	capcom.ResetAnimation();
	step = 0;
	timer.SetNewInterval(2000);
	changing = false;
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
			changing = true;

			//testing
			/*SceneMatchInfo info;
			info.player1Type = CharacterType::RYU;
			info.player2Type = CharacterType::KEN;
			info.stageType = StageType::HONDA;
			info.timeLimit = false;
			Scene* currentScene = new SceneMatch(info);
			servicesManager->scene->ChangeScene(currentScene);*/
			//end testing

			servicesManager->scene->ChangeScene(new SceneMainMenu());
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
