#include "MatchStateIntro.h"
#include "MatchStateFight.h"
#include "SceneMatch.h"
#include "SceneMatchGUI.h"
#include "Stage.h"
#include "Character.h"


MatchStateIntro::MatchStateIntro(SceneMatch* s) : MatchState{ s }
{
}

MatchStateIntro::~MatchStateIntro()
{
}

void MatchStateIntro::OnEnter()
{
	++scene->roundNumber;
	scene->GUI->SetMatchGUIState(SceneMatchGUI::MatchGUIState::INTRO);
}

MatchState* MatchStateIntro::UpdateState()
{
	scene->stage->UpdateState();
	scene->player1->UpdateState();
	scene->player2->UpdateState();
	scene->GUI->UpdateState();

	//Let the GUI do its job
	if (scene->GUI->StateHasFinished())
	{
		return new MatchStateFight(scene);
	}

	return nullptr;
}
