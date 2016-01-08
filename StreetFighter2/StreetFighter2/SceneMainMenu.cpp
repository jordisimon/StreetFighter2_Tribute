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
#include "Scene2PCharacterSelection.h"
#include "SceneMatchInfo.h"
#include "CharacterType.h"
#include "StageType.h"

#define MAX_OPTIONS 3

int SceneMainMenu::optionMoveSfx = -1;
int SceneMainMenu::optionSelectSfx = -1;


SceneMainMenu::SceneMainMenu(bool showMenu) : timer{1500}
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
	twwIntroSpeed = 120.0f;

	config->LoadSprite(capcomInfo, configSection, "capcomInfo");
	capcomInfoPos.x = screenCenter.x;
	capcomInfoPos.y = camera.h - capcomInfo.rect.h - 9;

	config->LoadSprite(options, configSection, "options");
	optionsPos.x = screenCenter.x;
	optionsPos.y = screenCenter.y + 50;

	config->LoadSprite(cursor, configSection, "cursor");
	cursorOriginalPos.x = screenCenter.x - (options.rect.w / 2) - 21;
	cursorOriginalPos.y = screenCenter.y + 55;

	firstStart = true;
	selectedOption = 0;

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

	cursorCurrentPos = cursorOriginalPos;

	currentState = nextState;
	if (firstStart)
	{
		servicesManager->audio->PlayMusic("Assets\\Sound\\Music\\MainMenu.ogg", 0.0f);
		firstStart = false;
	}
	SFLogoAnim.ResetAnimation();
	timer.SetNewInterval(1500);

	return true;
}

void SceneMainMenu::HandleOptionSelected()
{
	switch (selectedOption)
	{
	//Single player (not done)
	case 0:
		break;

	//VS Match
	case 1:
		if (!changing)
		{
			servicesManager->audio->PlayFx(optionSelectSfx);
			servicesManager->audio->StopMusic(2.0f);
			SceneMatchInfo info;
			info.twoPlayers = true;
			info.battleNumber = 0;
			info.player1Handicap = 3;
			info.player2Handicap = 3;
			info.player1Type = CharacterType::RYU;
			info.player2Type = CharacterType::KEN;
			info.stageType = StageType::RYU;
			HandleSceneChange(new Scene2PCharacterSelection(info));
		}
		break;

	//Options menu (not done)
	case 3:
		break;
	}
}

void SceneMainMenu::SetCursorPos()
{
	cursorCurrentPos = cursorOriginalPos;

	switch (selectedOption)
	{
	case 1:
		cursorCurrentPos.y += 16;
		break;

	case 2:
		cursorCurrentPos.y += 32;
		break;
	}
}

bool SceneMainMenu::HandleCommandAction(CommandAction action)
{
	switch (currentState)
	{
	case MainMenuState::INTRO_WAIT:
	case MainMenuState::LOGO_SPIN:
	case MainMenuState::TWW_IN:
	case MainMenuState::SCENE_COMPLETED:
		if(action == CommandAction::PAUSE)
		{
			nextState = MainMenuState::SHOW_MENU;
			servicesManager->fade->StartFading(this, this, 1.5f);
			changing = true;
			return true;
		}
		break;

	case MainMenuState::SHOW_MENU:
			switch (action)
			{
			case CommandAction::PAUSE:
				HandleOptionSelected();
				return true;
				break;

			case CommandAction::MOVE_UP:
				servicesManager->audio->PlayFx(optionMoveSfx);
				--selectedOption;
				if (selectedOption < 0)
					selectedOption = MAX_OPTIONS - 1;
				SetCursorPos();
				break;

			case CommandAction::MOVE_DOWN:
				servicesManager->audio->PlayFx(optionMoveSfx);
				++selectedOption;
				if (selectedOption >= MAX_OPTIONS)
					selectedOption = 0;
				SetCursorPos();
				break;
			}

		break;
	}

	return false;
}

bool SceneMainMenu::ProcessInput(CommandData * commandData)
{
	if (!changing)
	{
		for (const auto& command : commandData->p1Actions)
		{
			if (HandleCommandAction(command))
				return true;
		}

		for (const auto& command : commandData->p2Actions)
		{
			if (HandleCommandAction(command))
				return true;
		}
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
		servicesManager->render->BlitGUI(texture, cursor.GetRectPosition(cursorCurrentPos), cursor.rect);
		break;
	}

	return Entity::Result::R_OK;
}


