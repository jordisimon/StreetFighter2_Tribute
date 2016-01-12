#include "SF2Game.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceCommandManager.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"
#include "ServiceSceneManager.h"
#include "ParticleFactory.h"
#include "CommandContext.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "CommandState.h"
#include "SceneLicensed.h"

//Testing
#include "SceneMatch.h"
#include "SceneMatchInfo.h"
#include "Scene2PCharacterSelection.h"
#include "Scene2PHandicapAndStageSelection.h"
#include "Scene2PMatchResult.h"


SF2Game::SF2Game()
{
}


SF2Game::~SF2Game()
{
}

bool SF2Game::Init()
{
	//Set factory before calling inherited init to allow particles service to init factory
	servicesManager->particles->SetParticleFactory(new ParticleFactory());

	bool res = Game::Init();

	if (res)
	{
		//testing
		SceneMatchInfo info;
		info.twoPlayers = true;
		info.battleNumber = 0;
		info.player1Handicap = 3;
		info.player2Handicap = 3;
		info.player1Type = CharacterType::RYU;
		info.player2Type = CharacterType::KEN;
		info.stageType = StageType::GUILE;
		//servicesManager->scene->SetNewScene(new Scene2PCharacterSelection(info));
		//servicesManager->scene->SetNewScene(new Scene2PHandicapAndStageSelection(info));
		//servicesManager->scene->SetNewScene(new SceneMatch(info));
		//servicesManager->scene->SetNewScene(new Scene2PMatchResult(info));
		//end testing

		servicesManager->scene->SetNewScene(new SceneLicensed());

		//Debug
		debug = config->LoadBoolValue(DEBUG_SECTION, "enable", "0");
		debugCameraSpeed = config->LoadFloatValue(DEBUG_SECTION, "debugCameraSpeed", "3");
		debugCommandContext = servicesManager->commands->Load("Debug_Command_Context");
		debugCommandContext->AddCommandListener(this);
	}

	return res;
}

bool SF2Game::CleanUp()
{
	Game::CleanUp();

	return true;
}

bool SF2Game::UpdateInput() const
{
	bool result = Game::UpdateInput();

	if (result)
	{
		result = servicesManager->commands->ProcessInput(debugCommandContext);
	}
	return result;
}

bool SF2Game::ProcessInput(CommandData* commandData)
{
	if (servicesManager->commands->CommandExit())
	{
		exit = true;
	}
	else
	{
		if (debug)
		{
			for (const auto& command : commandData->globalActions)
			{
				switch (command)
				{
				case CommandAction::DBG_TOGGLE_VIEW_COLLITION:
					servicesManager->collitions->drawColliders = !servicesManager->collitions->drawColliders;
					break;
				}
			}

			for (const auto& command : commandData->globalStates)
			{
				switch (command)
				{
				case CommandState::DBG_MOVE_CAM_UP:
					servicesManager->render->MoveCamera(fPoint(0, -debugCameraSpeed));
					break;

				case CommandState::DBG_MOVE_CAM_DOWN:
					servicesManager->render->MoveCamera(fPoint(0, debugCameraSpeed));
					break;

				case CommandState::DBG_MOVE_CAM_LEFT:
					servicesManager->render->MoveCamera(fPoint(-debugCameraSpeed, 0));
					break;

				case CommandState::DBG_MOVE_CAM_RIGHT:
					servicesManager->render->MoveCamera(fPoint(debugCameraSpeed, 0));
					break;
				}
			}
		}
	}

	return true;
}

Game* CreateGame()
{
	return new SF2Game();
}
