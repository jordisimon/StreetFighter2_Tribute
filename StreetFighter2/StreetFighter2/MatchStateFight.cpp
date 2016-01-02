#include "MatchStateFight.h"
#include "SceneMatch.h"
#include "SceneMatchGUI.h"
#include "ServicesManager.h"
#include "ServiceCommandManager.h"
#include "ServiceCollition.h"
#include "ServiceParticles.h"
#include "CommandContext.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "MatchStatePause.h"
#include "MatchStateFinish.h"
#include "Character.h"
#include "Stage.h"

void MatchStateFight::OnEnter()
{
	if (scene->timeLimit)
		scene->timer.Resume();
	servicesManager->commands->SetCurrentContext(scene->commandContextFight);
	scene->GUI->SetMatchGUIState(SceneMatchGUI::MatchGUIState::FIGHT);
}

MatchState* MatchStateFight::ProcessInput(CommandData * commandData)
{
	for (const auto& command : commandData->p1Actions)
	{
		switch (command)
		{
		case CommandAction::PAUSE:
			return new MatchStatePause(scene, 1);
			break;
		}
	}

	for (const auto& command : commandData->p2Actions)
	{
		switch (command)
		{
		case CommandAction::PAUSE:
			return new MatchStatePause(scene,2);
			break;
		}
	}

	scene->player1->ProcessInput(commandData);
	scene->player2->ProcessInput(commandData);

	return nullptr;
}

MatchState * MatchStateFight::UpdateState()
{
	if (scene->timeLimit && scene->timer.Reached() && scene->time > 0)
	{
		--scene->time;
		scene->timer.Reset();
	}
	
	scene->UpdatePlayersAttacking();
	scene->CalculatePlayersDistance();
	scene->stage->UpdateState();
	servicesManager->particles->UpdateParticlesState();
	servicesManager->collitions->UpdateCollidersState();
	scene->player1->UpdateState();
	scene->player2->UpdateState();	
	scene->GUI->UpdateState();

	scene->MovePlayers();
	scene->ApplyForceToPlayers(scene->player1, scene->player2);
	scene->ApplyForceToPlayers(scene->player2, scene->player1);
	scene->CheckPlayerDirection();
	scene->SetCamYPosition();
	scene->SetCamXPosition();
	scene->SetCamPosition();

	bool matchFinished = (scene->timeLimit && scene->time <= 0) 
		|| (scene->player1->life <= 0) 
		|| (scene->player2->life <= 0);

	if (matchFinished)
		return new MatchStateFinish(scene);
	else
		return nullptr;
}
