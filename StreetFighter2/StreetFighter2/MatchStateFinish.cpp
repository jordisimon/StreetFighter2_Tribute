#include "MatchStateFinish.h"
#include "SceneMatch.h"
#include "SceneMatchGUI.h"
#include "Character.h"
#include "Stage.h"
#include "ServicesManager.h"
#include "ServiceParticles.h"
#include "MatchStateIntro.h"
#include "ServiceFade.h"


MatchStateFinish::MatchStateFinish(SceneMatch* s) : MatchState{ s }
{
}


MatchStateFinish::~MatchStateFinish()
{
}

void MatchStateFinish::OnEnter()
{
	finishGUI = false;
	shouldStartAnimations = false;
	//Calculate match outcome
	scene->winnerPlayer = 0;

	if (scene->player1->life != scene->player2->life)
	{
		if (scene->player1->life > scene->player2->life)
		{
			scene->winnerPlayer = 1;
			++scene->player1->roundVictories;
			if (scene->player1->life == 100)
				scene->vitalScore = 30000;
			else
				scene->vitalScore = scene->player1->life * 200;
		}
		else
		{
			scene->winnerPlayer = 2;
			++scene->player2->roundVictories;
			if (scene->player2->life == 100)
				scene->vitalScore = 30000;
			else
				scene->vitalScore = scene->player2->life * 200;
		}

		shouldStartAnimations = true;
	}

	if (scene->timeLimit)
		scene->timeScore = scene->time * 100;
	else
		scene->timeScore = 0;

	//Slow down
	scene->player1->updateOverallSpeed /= 4;
	scene->player2->updateOverallSpeed /= 4;

	scene->player1->RoundFinished(scene->winnerPlayer);
	scene->player2->RoundFinished(scene->winnerPlayer);

	if (scene->roundNumber == 4 ||
		scene->player1->roundVictories == 2 ||
		scene->player2->roundVictories == 2)
	{
		scene->player1->MatchFinished(scene->winnerPlayer);
		scene->player2->MatchFinished(scene->winnerPlayer);
	}
}


MatchState* MatchStateFinish::UpdateState()
{
	scene->player1->UpdateState();
	scene->player2->UpdateState();
	scene->stage->UpdateState();
	servicesManager->particles->UpdateParticlesState();
	scene->GUI->UpdateState();

	scene->MovePlayers();
	scene->ApplyForceToPlayers(scene->player1, scene->player2);
	scene->ApplyForceToPlayers(scene->player2, scene->player1);
	scene->CheckPlayerDirection();
	scene->UpdatePlayersCollidersPosition();
	scene->SetCamYPosition();
	scene->SetCamXPosition();
	scene->SetCamPosition();
	scene->SetCollidersPosition();

	if (scene->player1->position.y >= scene->stage->groundLevel && 
		scene->player2->position.y >= scene->stage->groundLevel &&
		!finishGUI)
	{
		if(shouldStartAnimations)
			scene->stage->StartFinishAnimations();
		scene->GUI->SetMatchGUIState(SceneMatchGUI::MatchGUIState::FINISH);
		finishGUI = true;
	}

	if (!scene->changing && scene->GUI->StateHasFinished())
	{
		//If this was the last round or any player has won 2 rounds
		//Exit match
		if (scene->roundNumber == 4 ||
			scene->player1->roundVictories == 2 ||
			scene->player2->roundVictories == 2)
		{
			scene->SceneChange();
		}
		else
		{
			//fade to black scene, scene
			servicesManager->fade->StartFading(scene, scene, 2.0f);
			scene->changing = true;
		}	
	}

	return nullptr;
}

