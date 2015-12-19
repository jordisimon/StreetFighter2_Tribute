#include "MatchStateIntro.h"
#include "ServicesManager.h"
#include "ServiceAudio.h"
#include "SceneMatch.h"
#include "SceneMatchGUI.h"
#include "Stage.h"
#include "Character.h"


MatchStateIntro::MatchStateIntro(SceneMatch* s) : MatchState{ s }, timer{1000}, step {0}
{
}

MatchStateIntro::~MatchStateIntro()
{
}

void MatchStateIntro::OnEnter()
{
	servicesManager->audio->PlayMusic(scene->stage->musicName, 0.0f);
	++scene->roundNumber;
}

State * MatchStateIntro::UpdateState()
{
	scene->stage->UpdateState();
	scene->player1->UpdateState();
	scene->player2->UpdateState();
	scene->GUI->UpdateState();

	if (timer.Reached())
	{
		++step;
		switch (step)
		{
		case 1: //Step 1: Round
			servicesManager->audio->PlayFx(scene->roundFx);
			timer.SetNewInterval(1000);
			break;

		case 2: //Step 2: #
			switch (scene->roundNumber)
			{
			case 1:
				servicesManager->audio->PlayFx(scene->oneFx);
				break;
			case 2:
				servicesManager->audio->PlayFx(scene->twoFx);
				break;
			case 3:
				servicesManager->audio->PlayFx(scene->threeFx);
				break;
			case 4:
				servicesManager->audio->PlayFx(scene->fourFx);
				break;
			}
			timer.SetNewInterval(1000);
			break;

		case 3: //Step 3: Fight
			servicesManager->audio->PlayFx(scene->fightFx);
			timer.SetNewInterval(1000);
			break;

		case 4: //Step 4: change to state fight
			return new MatchStateFight(scene);
			break;
		}
	}

	return nullptr;
}
