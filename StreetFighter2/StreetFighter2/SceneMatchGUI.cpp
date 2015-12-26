#include "SceneMatchGUI.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "Config.h"
#include "SceneMatch.h"
#include "Character.h"


SceneMatchGUI::SceneMatchGUI() : timer{1000}
{
	configSection = "Match_GUI";
}


SceneMatchGUI::~SceneMatchGUI()
{
}

bool SceneMatchGUI::Init()
{
	config->LoadSprite(lifeBar, configSection, "lifeBar");

	config->LoadSprite(p1Score, configSection, "p1Score");
	config->LoadSprite(p2Score, configSection, "p2Score");
	config->LoadSprite(recordScore, configSection, "recordScore");
	config->LoadAnimation(pause, configSection, "pause");

	config->LoadSprite(num0, configSection, "num0");
	config->LoadSprite(num1, configSection, "num1");
	config->LoadSprite(num2, configSection, "num2");
	config->LoadSprite(num3, configSection, "num3");
	config->LoadSprite(num4, configSection, "num4");
	config->LoadSprite(num5, configSection, "num5");
	config->LoadSprite(num6, configSection, "num6");
	config->LoadSprite(num7, configSection, "num7");
	config->LoadSprite(num8, configSection, "num8");
	config->LoadSprite(num9, configSection, "num9");
	config->LoadSprite(numInf, configSection, "numInf");

	config->LoadSprite(ryuName, configSection, "ryuName");
	config->LoadSprite(hondaName, configSection, "hondaName");
	config->LoadSprite(blankaName, configSection, "blankaName");
	config->LoadSprite(guileName, configSection, "guileName");
	config->LoadSprite(kenName, configSection, "kenName");
	config->LoadSprite(chunliName, configSection, "chunliName");
	config->LoadSprite(zanguiefName, configSection, "zanguiefName");
	config->LoadSprite(dalshimName, configSection, "dalshimName");

	config->LoadSprite(victory, configSection, "victory");
	config->LoadAnimation(round1, configSection, "round1");
	config->LoadAnimation(round2, configSection, "round2");
	config->LoadAnimation(round3, configSection, "round3");
	config->LoadAnimation(fRound, configSection, "fRound");
	config->LoadAnimation(fight, configSection, "fight");
	fight.loop = false;


	//Calculate positions
	const fPoint& screenCenter = servicesManager->render->GetScreenCenter();
	lifeBarPos.x = screenCenter.x - (lifeBar.rect.w / 2);
	lifeBarPos.y = 10;

	p1ScorePos.x = screenCenter.x - 120;
	p1ScorePos.y = 2;
	p2ScorePos.x = screenCenter.x + 48;
	p2ScorePos.y = 2;
	recordScorePos.x = screenCenter.x - 40;
	recordScorePos.y = 2;
	pause1Pos.x = screenCenter.x - 104;
	pause1Pos.y = 2;
	pause2Pos.x = screenCenter.x +64;
	pause2Pos.y = 2;

	barP1Pos.x = screenCenter.x - 8;
	barP1Pos.y = 13;

	barP2Pos.x = screenCenter.x + 8;
	barP2Pos.y = 13;

	digit1Pos.x = screenCenter.x - 8;
	digit1Pos.y = 27;
	digit2Pos.x = screenCenter.x;
	digit2Pos.y = 27;

	player1Name = GetSpriteName(scene->player1->characterId);
	namePlayer1Pos.x = screenCenter.x - 96;
	namePlayer1Pos.y = 26;

	player2Name = GetSpriteName(scene->player2->characterId);
	namePlayer2Pos.x = screenCenter.x + 96 - player2Name->rect.w;
	namePlayer2Pos.y = 26;

	roundFightPos.x = screenCenter.x - 28;
	roundFightPos.y = 55;

	return true;
}

bool SceneMatchGUI::CleanUp()
{
	//servicesManager->textures->Unload(texture);

	return true;
}

bool SceneMatchGUI::Start()
{
	texture = servicesManager->textures->Load(configSection);

	return true;
}

bool SceneMatchGUI::Stop()
{
	servicesManager->textures->Unload(texture);

	return true;
}



Entity::Result SceneMatchGUI::UpdateState()
{
	switch (currentState)
	{
	case SceneMatchGUI::MatchGUIState::INTRO:
		switch (introStep)
		{
		case 0: //Milliseconds wait
			if (timer.Reached())
			{
				++introStep;
			}
			break;
		case 1: //Round X fade in
			currentRoundFight->UpdateCurrentFrame();
			if (currentRoundFight->HasFinished())
			{
				++introStep;
				timer.SetNewInterval(750);
				timer.Reset();
			}
			break;

		case 2: //Milliseconds wait
			if (timer.Reached())
			{
				++introStep;
				currentRoundFight->forward = false;
				currentRoundFight->ResetAnimation();
			}
			break;

		case 3: //Round X fade out
			currentRoundFight->UpdateCurrentFrame();
			if (currentRoundFight->HasFinished())
			{
				++introStep;
				currentRoundFight = &fight;
			}
			break;

		case 4: //Fight fade in
			currentRoundFight->UpdateCurrentFrame();
			break;
		}
		break;
	case SceneMatchGUI::MatchGUIState::FIGHT:
		break;
	case SceneMatchGUI::MatchGUIState::PAUSE:
		pause.UpdateCurrentFrame();
		break;
	case SceneMatchGUI::MatchGUIState::FINISH:
		break;
	default:
		break;
	}
	
	return Result::R_OK;
}

Entity::Result SceneMatchGUI::Draw()
{
	//Common sprites
	//Record score
	servicesManager->render->BlitGUI(texture, recordScore.GetRectPosition(recordScorePos), recordScore.rect);

	//Life bar
	servicesManager->render->BlitGUI(texture, lifeBar.GetRectPosition(lifeBarPos), lifeBar.rect);

	servicesManager->render->SetDrawColor(Color(Color::Predefined::YELLOW));
	fRect lifeBar;
	lifeBar.h = 8;
	lifeBar.y = barP1Pos.y;

	//Bar player 1
	lifeBar.w = (float)scene->player1->life * 88 / 100;
	lifeBar.x = barP1Pos.x - lifeBar.w;
	servicesManager->render->DrawRectFill(lifeBar, true);

	//Bar player 2
	lifeBar.w = (float)scene->player2->life * 88 / 100;
	lifeBar.x = barP2Pos.x;
	servicesManager->render->DrawRectFill(lifeBar, true);

	//Time
	if (scene->timeLimit)
	{
		int firstDigit = (int)(scene->time / 10);
		Sprite* firstNumSprite = GetSpriteNum(firstDigit);
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(digit1Pos), firstNumSprite->rect);

		int secondDigit = scene->time % 10;
		Sprite* secondNumSprite = GetSpriteNum(secondDigit);
		servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(digit2Pos), secondNumSprite->rect);
	}
	else
	{
		servicesManager->render->BlitGUI(texture, numInf.GetRectPosition(digit1Pos), numInf.rect);
	}

	//Character name
	servicesManager->render->BlitGUI(texture, player1Name->GetRectPosition(namePlayer1Pos), player1Name->rect);
	servicesManager->render->BlitGUI(texture, player2Name->GetRectPosition(namePlayer2Pos), player2Name->rect);

	switch (currentState)
	{
	case MatchGUIState::PAUSE:
		servicesManager->render->BlitGUI(texture, pause.GetFrame().GetRectPosition(pause1Pos), pause.GetFrame().rect);
		servicesManager->render->BlitGUI(texture, pause.GetFrame().GetRectPosition(pause2Pos), pause.GetFrame().rect);
		break;

	case MatchGUIState::FIGHT:
		//Players score
		servicesManager->render->BlitGUI(texture, p1Score.GetRectPosition(p1ScorePos), p1Score.rect);
		servicesManager->render->BlitGUI(texture, p2Score.GetRectPosition(p2ScorePos), p2Score.rect);
		break;

	case MatchGUIState::INTRO:
		//Players score
		servicesManager->render->BlitGUI(texture, p1Score.GetRectPosition(p1ScorePos), p1Score.rect);
		servicesManager->render->BlitGUI(texture, p2Score.GetRectPosition(p2ScorePos), p2Score.rect);

		if (introStep >0)
			servicesManager->render->BlitGUI(texture, currentRoundFight->GetFrame().GetRectPosition(roundFightPos), currentRoundFight->GetFrame().rect);

		break;
	}	

	return Result::R_OK;
}


Sprite* SceneMatchGUI::GetSpriteNum(int number)
{
	switch (number)
	{
	case 0:
		return &num0;
	case 1:
		return &num1;
	case 2:
		return &num2;
	case 3:
		return &num3;
	case 4:
		return &num4;
	case 5:
		return &num5;
	case 6:
		return &num6;
	case 7:
		return &num7;
	case 8:
		return &num8;
	case 9:
		return &num9;
	}

	return nullptr;
}

Sprite* SceneMatchGUI::GetSpriteName(int characterId)
{
	switch (characterId)
	{
	case 0:
		return &ryuName;
	case 1:
		return &hondaName;
	case 2:
		return &blankaName;
	case 3:
		return &guileName;
	case 4:
		return &kenName;
	case 5:
		return &chunliName;
	case 6:
		return &zanguiefName;
	case 7:
		return &dalshimName;
	}
	return nullptr;
}

void SceneMatchGUI::SetMatchGUIState(MatchGUIState state)
{
	currentState = state;

	//On enter state
	switch (state)
	{
	case SceneMatchGUI::MatchGUIState::INTRO:
		introStep = 0;
		switch (scene->roundNumber)
		{
		case 1:
			currentRoundFight = &round1;
			break;
		case 2:
			currentRoundFight = &round2;
			break;
		case 3:
			currentRoundFight = &round3;
			break;
		case 4:
			currentRoundFight = &fRound;
			break;
		}
		currentRoundFight->loop = false;
		currentRoundFight->forward = true;
		currentRoundFight->ResetAnimation();
		break;
	case SceneMatchGUI::MatchGUIState::FIGHT:
		break;
	case SceneMatchGUI::MatchGUIState::PAUSE:
		pause.ResetAnimation();
		break;
	case SceneMatchGUI::MatchGUIState::FINISH:
		break;
	default:
		break;
	}
}
