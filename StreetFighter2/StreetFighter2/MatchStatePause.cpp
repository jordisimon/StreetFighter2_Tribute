#include "MatchStatePause.h"
#include "SceneMatch.h"
#include "SceneMatchGUI.h"
#include "ServicesManager.h"
#include "ServiceCommandManager.h"
#include "ServiceAudio.h"
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
	if (scene->timeLimit)
		scene->timer.Pause();
	servicesManager->commands->SetCurrentContext(scene->commandContextPause);
	servicesManager->audio->PauseMusic();
	servicesManager->audio->PlayFx(scene->pauseFx);
}

void MatchStatePause::OnExit()
{
	servicesManager->audio->PlayFx(scene->fightFx);
	servicesManager->audio->ResumeMusic();
	scene->paused = false;
}

State* MatchStatePause::ProcessInput(CommandData * commandData)
{
	for (const auto& command : commandData->actions)
	{
		switch (command)
		{
		case CommandAction::P1_PAUSE:
			if (playerPaused == 1)
				return new MatchStateFight(scene);
			break;
		case CommandAction::P2_PAUSE:
			if (playerPaused == 2)
				return new MatchStateFight(scene);
			break;
		}
	}

	return nullptr;
}

State * MatchStatePause::UpdateState()
{
	scene->GUI->UpdateState();
	return nullptr;
}
