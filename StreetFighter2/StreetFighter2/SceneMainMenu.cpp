#include "SceneMainMenu.h"
#include "Config.h"
#include "Rect.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "ServiceTextures.h"
#include "ServiceAudio.h"
#include "ServiceTime.h"
#include "ServiceFade.h"
#include "ServiceCommandManager.h"
#include "CommandContext.h"
#include "CommandData.h"
#include "CommandAction.h"

int SceneMainMenu::optionMoveSfx = -1;
int SceneMainMenu::optionSelectSfx = -1;


SceneMainMenu::SceneMainMenu(bool showMenu) : timer{3000}
{
	configSection = "Scene_Intro";
	configSectionAnim = "Scene_Intro_Logo";

	if (showMenu)
		nextState = MainMenuState::SHOW_MENU;
	else
		nextState = MainMenuState::INTRO_WAIT;

	commandContextMenu = servicesManager->commands->Load("Menu_Command_Context");
	servicesManager->commands->SetCurrentContext(commandContextMenu);

	if (optionMoveSfx == -1) optionMoveSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Menu\\optionMove.ogg");
	if (optionSelectSfx == -1) optionSelectSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Menu\\optionSelect.ogg");
}


SceneMainMenu::~SceneMainMenu()
{
}

bool SceneMainMenu::Init()
{
	const fPoint& screenCenter = servicesManager->render->GetScreenCenter();
	const fRect& camera = servicesManager->render->GetCamera();

	texture = servicesManager->textures->Load(configSection);
	textureAnim = servicesManager->textures->Load(configSectionAnim);

	commandContextMenu->AddCommandListener(this);

	config->LoadSprite(SFLogo, configSection, "SFLogo");
	config->LoadAnimation(SFLogoAnim, configSectionAnim, "SFLogoAnim");
	SFLogoPos.x = screenCenter.x;
	SFLogoPos.y = screenCenter.y - 35;

	config->LoadSprite(tww1, configSection, "tww1");
	config->LoadSprite(tww2, configSection, "tww2");
	tww1CurrentPos.x = -90;
	tww1CurrentPos.y = screenCenter.y + 28;
	tww2CurrentPos.x = camera.w + 90;
	tww2CurrentPos.y = screenCenter.y + 28;
	twwFinalPos.x = screenCenter.x;
	twwFinalPos.y = screenCenter.y + 28;
	twwIntroSpeed = 80.0f;

	config->LoadSprite(capcomInfo, configSection, "capcomInfo");
	capcomInfoPos.x = screenCenter.x;
	capcomInfoPos.y = camera.h - capcomInfo.rect.h - 9;

	config->LoadSprite(options, configSection, "options");
	optionsPos.x = screenCenter.x;
	optionsPos.y = screenCenter.y + 50;

	config->LoadSprite(cursor, configSection, "cursor");
	cursorPos.x = screenCenter.x - (options.rect.w / 2) - 21;
	cursorPos.y = screenCenter.y + 55;

	firstStart = true;

	return true;
}

bool SceneMainMenu::CleanUp()
{
	servicesManager->textures->Unload(textureAnim);
	commandContextMenu->RemoveCommandListener(this);
	return true;
}

bool SceneMainMenu::Start()
{
	Scene::Start();

	currentState = nextState;
	if (firstStart)
	{
		servicesManager->audio->PlayMusic("Assets\\Sound\\Music\\MainMenu.ogg", 0.0f);
		firstStart = false;
	}
	SFLogoAnim.ResetAnimation();
	timer.SetNewInterval(3000);

	return true;
}

bool SceneMainMenu::ProcessInput(CommandData * commandData)
{
	switch (currentState)
	{
	case MainMenuState::LOGO_SPIN:
	case MainMenuState::TWW_IN:
	case MainMenuState::SCENE_COMPLETED:
		for (const auto& command : commandData->p1Actions)
		{
			switch (command)
			{
			case CommandAction::PAUSE:
				nextState = MainMenuState::SHOW_MENU;
				servicesManager->fade->StartFading(this, this, 2.0f);
				return true;
				break;
			}
		}

		for (const auto& command : commandData->p2Actions)
		{
			switch (command)
			{
			case CommandAction::PAUSE:
				nextState = MainMenuState::SHOW_MENU;
				servicesManager->fade->StartFading(this, this, 2.0f);
				return true;
				break;
			}
		}
		break;

	case MainMenuState::SHOW_MENU:
		for (const auto& command : commandData->p1Actions)
		{
			switch (command)
			{
			case CommandAction::PAUSE:
				nextState = MainMenuState::SHOW_MENU;
				servicesManager->fade->StartFading(this, this, 2.0f);
				return true;
				break;
			}
		}

		for (const auto& command : commandData->p2Actions)
		{
			switch (command)
			{
			case CommandAction::PAUSE:
				nextState = MainMenuState::SHOW_MENU;
				servicesManager->fade->StartFading(this, this, 2.0f);
				return true;
				break;
			}
		}
		break;
	default:
		break;
	}

	return true;
}

Entity::Result SceneMainMenu::UpdateState()
{
	switch (currentState)
	{
	case MainMenuState::INTRO_WAIT:
		if (timer.Reached())
			currentState = MainMenuState::LOGO_SPIN;
		break;

	case MainMenuState::LOGO_SPIN:
		if (SFLogoAnim.HasFinished())
			currentState = MainMenuState::TWW_IN;
		SFLogoAnim.UpdateCurrentFrame();
		break;

	case MainMenuState::TWW_IN:
		float movement = twwIntroSpeed * servicesManager->time->frameTimeSeconds;
		tww1CurrentPos.x += movement;
		tww2CurrentPos.x -= movement;

		if (tww1CurrentPos.x >= servicesManager->render->GetScreenCenter().x)
		{
			currentState = MainMenuState::SCENE_COMPLETED;
		}
	}
	return Entity::Result::R_OK;
}

Entity::Result SceneMainMenu::Draw() const
{
	switch (currentState)
	{
	case MainMenuState::INTRO_WAIT:
	case MainMenuState::LOGO_SPIN:
		servicesManager->render->BlitGUI(textureAnim, SFLogoAnim.GetFrame().GetRectPosition(SFLogoPos), SFLogoAnim.GetFrame().rect);
		break;

	case MainMenuState::TWW_IN:
		servicesManager->render->BlitGUI(texture, SFLogo.GetRectPosition(SFLogoPos), SFLogo.rect);
		servicesManager->render->BlitGUI(texture, tww1.GetRectPosition(tww1CurrentPos), tww1.rect);
		servicesManager->render->BlitGUI(texture, tww2.GetRectPosition(tww2CurrentPos), tww2.rect);
		servicesManager->render->BlitGUI(texture, capcomInfo.GetRectPosition(capcomInfoPos), capcomInfo.rect);
		break;

	case MainMenuState::SCENE_COMPLETED:
		servicesManager->render->BlitGUI(texture, SFLogo.GetRectPosition(SFLogoPos), SFLogo.rect);
		servicesManager->render->BlitGUI(texture, tww1.GetRectPosition(twwFinalPos), tww1.rect);
		servicesManager->render->BlitGUI(texture, tww2.GetRectPosition(twwFinalPos), tww2.rect);
		servicesManager->render->BlitGUI(texture, capcomInfo.GetRectPosition(capcomInfoPos), capcomInfo.rect);
		break;

	case MainMenuState::SHOW_MENU:
		servicesManager->render->BlitGUI(texture, SFLogo.GetRectPosition(SFLogoPos), SFLogo.rect);
		servicesManager->render->BlitGUI(texture, tww1.GetRectPosition(twwFinalPos), tww1.rect);
		servicesManager->render->BlitGUI(texture, tww2.GetRectPosition(twwFinalPos), tww2.rect);
		servicesManager->render->BlitGUI(texture, options.GetRectPosition(optionsPos), options.rect);
		servicesManager->render->BlitGUI(texture, cursor.GetRectPosition(cursorPos), cursor.rect);
		break;
	}

	return Entity::Result::R_OK;
}


