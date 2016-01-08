#include "MatchStatePause.h"
#include "SceneMatch.h"
#include "SceneMatchGUI.h"
#include "ServicesManager.h"
#include "ServiceCommandManager.h"
#include "ServiceTime.h"
#include "CommandContext.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "MatchStateFight.h"


MatchStatePause::MatchStatePause(SceneMatch* s, unsigned int player) : MatchState{ s }, playerPaused{ player }
{
}

MatchStatePause::~MatchStatePause()
{
}

void MatchStatePause::OnEnter()
{
	scene->paused = true;
	scene->PauseAllTimers();
	servicesManager->commands->SetCurrentContext(scene->commandContextPause);
	
	scene->GUI->SetMatchGUIState(SceneMatchGUI::MatchGUIState::PAUSE);
}

void MatchStatePause::OnExit()
{
	scene->paused = false;
	servicesManager->time->Update(); //To avoid counting all paused time as frame time
}

MatchState* MatchStatePause::ProcessInput(CommandData * commandData)
{
	for (const auto& command : commandData->p1Actions)
	{
		switch (command)
		{
		case CommandAction::PAUSE:
			if (playerPaused == 1)
				return new MatchStateFight(scene);
			break;
		}
	}

	for (const auto& command : commandData->p2Actions)
	{
		switch (command)
		{
		case CommandAction::PAUSE:
			if (playerPaused == 2)
				return new MatchStateFight(scene);
			break;
		}
	}

	return nullptr;
}

MatchState * MatchStatePause::UpdateState()
{
	scene->GUI->UpdateState();
	return nullptr;
}
