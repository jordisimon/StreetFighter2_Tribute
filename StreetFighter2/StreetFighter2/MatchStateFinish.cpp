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
	fading = false;
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

		scene->stage->StartFinishAnimations();
	}

	if (scene->timeLimit)
		scene->timeScore = scene->time * 100;
	else
		scene->timeScore = 0;

	scene->GUI->SetMatchGUIState(SceneMatchGUI::MatchGUIState::FINISH);
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
	scene->SetCamYPosition();
	scene->SetCamXPosition();
	scene->SetCamPosition();

	if (scene->GUI->StateHasFinished())
	{
		//If this was the last round or any player has won 2 rounds
		//Exit match
		if (scene->roundNumber == 4 ||
			scene->player1->roundVictories == 2 ||
			scene->player2->roundVictories == 2)
		{
			//Scene manager load scene XXX
		}
		else
		{
			//fade to black scene, scene
			if (!fading)
			{
				servicesManager->fade->StartFading(scene, scene, 2.0f);
				fading = true;
			}
		}	
	}

	return nullptr;
}

