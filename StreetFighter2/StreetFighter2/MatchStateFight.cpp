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


MatchStateFight::MatchStateFight(SceneMatch* s) : MatchState{ s }
{
}


MatchStateFight::~MatchStateFight()
{
}

void MatchStateFight::OnEnter()
{
	if (scene->timeLimit)
		scene->timer.Resume();
	servicesManager->commands->SetCurrentContext(scene->commandContextFight);
	scene->GUI->SetMatchGUIState(SceneMatchGUI::MatchGUIState::FIGHT);
}

void MatchStateFight::OnExit()
{
}

State * MatchStateFight::ProcessInput(CommandData * commandData)
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

State * MatchStateFight::UpdateState()
{
	//TODO:
	/*
		delegate update state to entities

		check boundaries of players and its direction
		update time

		check finish condition (time = 0 or playerX->life = 0)
		if finish change state to finish
	*/

	if (scene->timeLimit && scene->timer.Reached() && scene->time > 0)
	{
		--scene->time;
		scene->timer.Reset();
	}
	

	scene->stage->UpdateState();
	scene->player1->UpdateState();
	scene->player2->UpdateState();
	servicesManager->particles->UpdateParticlesState();
	servicesManager->collitions->UpdateCollidersState();
	scene->GUI->UpdateState();

	bool matchFinished = (scene->timeLimit && scene->time <= 0) 
		|| (scene->player1->life <= 0) 
		|| (scene->player2->life <= 0);

	if (matchFinished)
		return new MatchStateFinish(scene);
	else
		return nullptr;
}
