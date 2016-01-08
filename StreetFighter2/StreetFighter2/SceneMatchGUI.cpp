#include "SceneMatchGUI.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceAudio.h"
#include "ServiceRender.h"
#include "ServiceTime.h"
#include "Config.h"
#include "SceneMatch.h"
#include "Stage.h"
#include "Character.h"
#include "SF2Stats.h"
#include "PlayerStats.h"
#include "CharacterStats.h"

int SceneMatchGUI::pauseFx = -1;
int SceneMatchGUI::roundFx = -1;
int SceneMatchGUI::oneFx = -1;
int SceneMatchGUI::twoFx = -1;
int SceneMatchGUI::threeFx = -1;
int SceneMatchGUI::fourFx = -1;
int SceneMatchGUI::fightFx = -1;
int SceneMatchGUI::perfectFx = -1;
int SceneMatchGUI::bonusShortFx = -1;
int SceneMatchGUI::bonusFx = -1;



SceneMatchGUI::SceneMatchGUI() : timer{1000}
{
	configSection = "Match_GUI";

	if (pauseFx == -1) pauseFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\Pause.ogg");
	if (roundFx == -1) roundFx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\Match\\Round.ogg");
	if (oneFx == -1) oneFx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\Match\\One.ogg");
	if (twoFx == -1) twoFx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\Match\\Two.ogg");
	if (threeFx == -1) threeFx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\Match\\Three.ogg");
	if (fourFx == -1) fourFx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\Match\\Four.ogg");
	if (fightFx == -1) fightFx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\Match\\Fight.ogg");
	if (perfectFx == -1) perfectFx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\Match\\Perfect.ogg");
	if (bonusShortFx == -1) bonusShortFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\BonusShort.ogg");
	if (bonusFx == -1) bonusFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Match\\Bonus.ogg");
}

SceneMatchGUI::~SceneMatchGUI()
{
}

bool SceneMatchGUI::Init()
{
	texture = servicesManager->textures->Load(configSection);

	//To calculate positions
	const fPoint& screenCenter = servicesManager->render->GetScreenCenter();
	
	config->LoadSprite(lifeBar, configSection, "lifeBar");
	lifeBarPos.x = screenCenter.x;
	lifeBarPos.y = 11;

	config->LoadAnimation(redKO, configSection, "redKO");
	redKOPos.x = screenCenter.x;
	redKOPos.y = 11;

	barP1Pos.x = (int)screenCenter.x - 8;
	barP1Pos.y = 14;
	barP2Pos.x = (int)screenCenter.x + 8;
	barP2Pos.y = 14;

	config->LoadSprite(p1Score, configSection, "p1Score");
	p1ScorePos.x = screenCenter.x - 120;
	p1ScorePos.y = 2;
	config->LoadSprite(p2Score, configSection, "p2Score");
	p2ScorePos.x = screenCenter.x + 48;
	p2ScorePos.y = 2;
	config->LoadSprite(recordScore, configSection, "recordScore");
	recordScorePos.x = screenCenter.x - 40;
	recordScorePos.y = 2;
	config->LoadSprite(originalRecordScore, configSection, "originalRecordScore");
	config->LoadAnimation(pause, configSection, "pause");
	pause1Pos.x = screenCenter.x - 104;
	pause1Pos.y = 2;
	pause2Pos.x = screenCenter.x + 64;
	pause2Pos.y = 2;

	p1ScoreNumberPos.x = screenCenter.x - 96;
	p1ScoreNumberPos.y = 2;

	p2ScoreNumberPos.x = screenCenter.x + 72;
	p2ScoreNumberPos.y = 2;

	recordScoreNumberPos.x = screenCenter.x - 8;
	recordScoreNumberPos.y = 2;

	config->LoadAnimation(num0, configSection, "num0");
	timeNumbers.push_back(&num0);
	config->LoadAnimation(num1, configSection, "num1");
	timeNumbers.push_back(&num1);
	config->LoadAnimation(num2, configSection, "num2");
	timeNumbers.push_back(&num2);
	config->LoadAnimation(num3, configSection, "num3");
	timeNumbers.push_back(&num3);
	config->LoadAnimation(num4, configSection, "num4");
	timeNumbers.push_back(&num4);
	config->LoadAnimation(num5, configSection, "num5");
	timeNumbers.push_back(&num5);
	config->LoadAnimation(num6, configSection, "num6");
	timeNumbers.push_back(&num6);
	config->LoadAnimation(num7, configSection, "num7");
	timeNumbers.push_back(&num7);
	config->LoadAnimation(num8, configSection, "num8");
	timeNumbers.push_back(&num8);
	config->LoadAnimation(num9, configSection, "num9");
	timeNumbers.push_back(&num9);
	config->LoadSprite(numInf, configSection, "numInf");
	timeDigit1Pos.x = screenCenter.x - 8;
	timeDigit1Pos.y = 27;
	timeDigit2Pos.x = screenCenter.x;
	timeDigit2Pos.y = 27;

	config->LoadSprite(numScoreBig0, configSection, "numScoreBig0");
	scoreBigNumbers.push_back(&numScoreBig0);
	config->LoadSprite(numScoreBig1, configSection, "numScoreBig1");
	scoreBigNumbers.push_back(&numScoreBig1);
	config->LoadSprite(numScoreBig2, configSection, "numScoreBig2");
	scoreBigNumbers.push_back(&numScoreBig2);
	config->LoadSprite(numScoreBig3, configSection, "numScoreBig3");
	scoreBigNumbers.push_back(&numScoreBig3);
	config->LoadSprite(numScoreBig4, configSection, "numScoreBig4");
	scoreBigNumbers.push_back(&numScoreBig4);
	config->LoadSprite(numScoreBig5, configSection, "numScoreBig5");
	scoreBigNumbers.push_back(&numScoreBig5);
	config->LoadSprite(numScoreBig6, configSection, "numScoreBig6");
	scoreBigNumbers.push_back(&numScoreBig6);
	config->LoadSprite(numScoreBig7, configSection, "numScoreBig7");
	scoreBigNumbers.push_back(&numScoreBig7);
	config->LoadSprite(numScoreBig8, configSection, "numScoreBig8");
	scoreBigNumbers.push_back(&numScoreBig8);
	config->LoadSprite(numScoreBig9, configSection, "numScoreBig9");
	scoreBigNumbers.push_back(&numScoreBig9);

	config->LoadSprite(numScoreLittle0, configSection, "numScoreLittle0");
	scoreLittleNumbers.push_back(&numScoreLittle0);
	config->LoadSprite(numScoreLittle1, configSection, "numScoreLittle1");
	scoreLittleNumbers.push_back(&numScoreLittle1);
	config->LoadSprite(numScoreLittle2, configSection, "numScoreLittle2");
	scoreLittleNumbers.push_back(&numScoreLittle2);
	config->LoadSprite(numScoreLittle3, configSection, "numScoreLittle3");
	scoreLittleNumbers.push_back(&numScoreLittle3);
	config->LoadSprite(numScoreLittle4, configSection, "numScoreLittle4");
	scoreLittleNumbers.push_back(&numScoreLittle4);
	config->LoadSprite(numScoreLittle5, configSection, "numScoreLittle5");
	scoreLittleNumbers.push_back(&numScoreLittle5);
	config->LoadSprite(numScoreLittle6, configSection, "numScoreLittle6");
	scoreLittleNumbers.push_back(&numScoreLittle6);
	config->LoadSprite(numScoreLittle7, configSection, "numScoreLittle7");
	scoreLittleNumbers.push_back(&numScoreLittle7);
	config->LoadSprite(numScoreLittle8, configSection, "numScoreLittle8");
	scoreLittleNumbers.push_back(&numScoreLittle8);
	config->LoadSprite(numScoreLittle9, configSection, "numScoreLittle9");
	scoreLittleNumbers.push_back(&numScoreLittle9);

	config->LoadSprite(numBattle0, configSection, "numBattle0");
	battleNumbers.push_back(&numBattle0);
	config->LoadSprite(numBattle1, configSection, "numBattle1");
	battleNumbers.push_back(&numBattle1);
	config->LoadSprite(numBattle2, configSection, "numBattle2");
	battleNumbers.push_back(&numBattle2);
	config->LoadSprite(numBattle3, configSection, "numBattle3");
	battleNumbers.push_back(&numBattle3);
	config->LoadSprite(numBattle4, configSection, "numBattle4");
	battleNumbers.push_back(&numBattle4);
	config->LoadSprite(numBattle5, configSection, "numBattle5");
	battleNumbers.push_back(&numBattle5);
	config->LoadSprite(numBattle6, configSection, "numBattle6");
	battleNumbers.push_back(&numBattle6);
	config->LoadSprite(numBattle7, configSection, "numBattle7");
	battleNumbers.push_back(&numBattle7);
	config->LoadSprite(numBattle8, configSection, "numBattle8");
	battleNumbers.push_back(&numBattle8);
	config->LoadSprite(numBattle9, configSection, "numBattle9");
	battleNumbers.push_back(&numBattle9);

	player1Name = LoadSpriteName(scene->player1->characterId);
	player1NamePos.x = screenCenter.x - 96;
	player1NamePos.y = 26;

	player2Name = LoadSpriteName(scene->player2->characterId);
	player2NamePos.x = screenCenter.x + 96 - player2Name->rect.w;
	player2NamePos.y = 26;

	player1Wins = LoadNameWins(scene->player1->characterId);
	player2Wins = LoadNameWins(scene->player2->characterId);

	config->LoadAnimation(perfect, configSection, "perfect");

	config->LoadSprite(timeOver, configSection, "timeOver");
	config->LoadSprite(drawGame, configSection, "drawGame");
	config->LoadSprite(doubleKO, configSection, "doubleKO");

	finishMatcInfoPos.x = screenCenter.x;
	finishMatcInfoPos.y = 58;

	config->LoadSprite(time, configSection, "time");
	timePos.x = screenCenter.x - 44;
	timePos.y = 50;
	timeScorePos.x = screenCenter.x + 4;
	timeScorePos.y = 48;
	config->LoadSprite(vital, configSection, "vital");
	vitalPos.x = screenCenter.x - 44;
	vitalPos.y = 67;
	vitalScorePos.x = screenCenter.x + 4;
	vitalScorePos.y = 64;
	config->LoadSprite(bonus, configSection, "bonus");
	bonusPos.x = screenCenter.x - 44;
	bonusPos.y = 91;
	bonusScorePos.x = screenCenter.x + 4;
	bonusScorePos.y = 88;

	config->LoadSprite(victory, configSection, "victory");
	victoryP11Pos.x = screenCenter.x - 119;
	victoryP11Pos.y = 11;
	victoryP12Pos.x = screenCenter.x - 108;
	victoryP12Pos.y = 11;
	victoryP21Pos.x = screenCenter.x + 119;
	victoryP21Pos.y = 11;
	victoryP22Pos.x = screenCenter.x + 108;
	victoryP22Pos.y = 11;

	config->LoadAnimation(round1, configSection, "round1");
	config->LoadAnimation(round2, configSection, "round2");
	config->LoadAnimation(round3, configSection, "round3");
	config->LoadAnimation(fRound, configSection, "fRound");
	config->LoadAnimation(fight, configSection, "fight");

	roundFightPos.x = screenCenter.x - 28;
	roundFightPos.y = 55;

	config->LoadSprite(battle, configSection, "battle");
	battlePos.x = screenCenter.x - 35;
	battlePos.y = 87;

	battleDigit1Pos.x = screenCenter.x + 19;
	battleDigit1Pos.y = 87;
	battleDigit2Pos.x = screenCenter.x + 27;
	battleDigit2Pos.y = 87;

	return true;
}

bool SceneMatchGUI::CleanUp()
{
	RELEASE(player1Name);
	RELEASE(player2Name);
	RELEASE(player1Wins);
	RELEASE(player2Wins);

	servicesManager->textures->Unload(texture);

	return true;
}

bool SceneMatchGUI::Start()
{
	tempScore = 0;
	bonusScore = 0;
	return true;
}

void SceneMatchGUI::SetMatchGUIState(MatchGUIState state)
{
	//On exit state
	switch (currentState)
	{
	case SceneMatchGUI::MatchGUIState::PAUSE:
		servicesManager->audio->PlayFx(fightFx);
		servicesManager->audio->ResumeMusic();
		break;
	}

	currentState = state;
	stateFinished = false;
	stateStep = 0;

	//On enter state
	switch (state)
	{
	case SceneMatchGUI::MatchGUIState::INTRO:
		servicesManager->audio->PlayMusic(scene->stage->musicName, 0.0f);
		switch (scene->roundNumber)
		{
		case 1:
			currentRoundFight = &round1;
			currentRoundFx = oneFx;
			break;
		case 2:
			currentRoundFight = &round2;
			currentRoundFx = twoFx;
			break;
		case 3:
			currentRoundFight = &round3;
			currentRoundFx = threeFx;
			break;
		case 4:
			currentRoundFight = &fRound;
			currentRoundFx = fourFx;
			break;
		}
		currentRoundFight->forward = true;
		currentRoundFight->ResetAnimation();
		timer.SetNewInterval(2000);
		
		break;
	case SceneMatchGUI::MatchGUIState::FIGHT:
		break;
	case SceneMatchGUI::MatchGUIState::PAUSE:
		servicesManager->audio->PauseMusic();
		servicesManager->audio->PlayFx(pauseFx);
		pause.ResetAnimation();
		break;
	case SceneMatchGUI::MatchGUIState::FINISH:
		servicesManager->audio->StopMusic(2.0f);
		showTimeOver = false;
		showDoubleKO = false;
		showDrawGame = false;
		showP1Win = false;
		showP2Win = false;
		showPerfect = false;
		showScores = false;
		player1Wins->ResetAnimation();
		player2Wins->ResetAnimation();
		perfect.ResetAnimation();
		num0.ResetAnimation();
		num1.ResetAnimation();
		num2.ResetAnimation();
		num3.ResetAnimation();
		num4.ResetAnimation();
		num5.ResetAnimation();
		num6.ResetAnimation();
		num7.ResetAnimation();
		num8.ResetAnimation();
		num9.ResetAnimation();
		redKO.ResetAnimation();
		tempScore = scene->vitalScore + scene->timeScore;
		timer.SetNewInterval(1000);
		break;
	default:
		break;
	}
}

Entity::Result SceneMatchGUI::UpdateState()
{
	switch (currentState)
	{
	case SceneMatchGUI::MatchGUIState::INTRO:
		return UpdateIntro();

	case SceneMatchGUI::MatchGUIState::FIGHT:
		return UpdateFight();

	case SceneMatchGUI::MatchGUIState::PAUSE:
		return UpdatePause();

	case SceneMatchGUI::MatchGUIState::FINISH:
		return UpdateFinish();

	default:
		return Result::R_OK;
	}
}

Entity::Result SceneMatchGUI::UpdateIntro()
{
	switch (stateStep)
	{
	case 0: //Milliseconds wait
		if (timer.Reached())
		{
			++stateStep;
			servicesManager->audio->PlayFx(roundFx);
		}
		break;
	case 1: //Round X fade in				
		if (currentRoundFight->HasFinished())
		{
			++stateStep;
			timer.SetNewInterval(100);
			timer.Reset();
		}
		currentRoundFight->UpdateCurrentFrame();
		break;
	case 2: //Round number fx
		if (timer.Reached())
		{
			servicesManager->audio->PlayFx(currentRoundFx);
			++stateStep;
			timer.SetNewInterval(650);
			timer.Reset();
		}

	case 3: //Milliseconds wait
		if (timer.Reached())
		{
			++stateStep;
			currentRoundFight->forward = false;
			currentRoundFight->ResetAnimation();
		}
		break;

	case 4: //Round X fade out
		currentRoundFight->UpdateCurrentFrame();
		if (currentRoundFight->HasFinished())
		{
			++stateStep;
			currentRoundFight = &fight;
			servicesManager->audio->PlayFx(fightFx);
		}
		break;

	case 5: //Fight fade in
		if (currentRoundFight->HasFinished())
		{
			++stateStep;
			timer.SetNewInterval(250);
			timer.Reset();
		}
		currentRoundFight->UpdateCurrentFrame();
		break;
	case 6: //Milliseconds wait
		if (timer.Reached())
		{
			stateFinished = true;
		}
		break;
	}

	return Result::R_OK;
}

Entity::Result SceneMatchGUI::UpdateFight()
{
	if (scene->time < 15)
	{
		num0.UpdateCurrentFrame();
		num1.UpdateCurrentFrame();
		num2.UpdateCurrentFrame();
		num3.UpdateCurrentFrame();
		num4.UpdateCurrentFrame();
		num5.UpdateCurrentFrame();
		num6.UpdateCurrentFrame();
		num7.UpdateCurrentFrame();
		num8.UpdateCurrentFrame();
		num9.UpdateCurrentFrame();
	}

	if (scene->player1->life < 50 || scene->player2->life < 50)
	{
		redKO.UpdateCurrentFrame();
	}

	return Result::R_OK;
}

Entity::Result SceneMatchGUI::UpdatePause()
{
	pause.UpdateCurrentFrame();
	return Result::R_OK;
}

Entity::Result SceneMatchGUI::UpdateFinish()
{
	switch (stateStep)
	{
	case 0:
		if (timer.Reached())
		{
			++stateStep;
		}
		break;

	case 1:
		if (scene->timeLimit && scene->time <= 0 && !(scene->player1->life <= 0 || scene->player2->life <= 0))
		{
			showTimeOver = true;
			timer.SetNewInterval(2000);
			++stateStep;
		}
		else
			stateStep = 3;
		break;

	case 2:
		if (timer.Reached())
		{
			showTimeOver = false;
			++stateStep;
		}
		break;

	case 3:
		if (scene->player1->life == 0 && scene->player2->life == 0)
			showDoubleKO = true;
		else if (scene->player1->life == scene->player2->life)
			showDrawGame = true;
		else if (scene->player1->life > scene->player2->life)
			showP1Win = true;
		else
			showP2Win = true;

		timer.SetNewInterval(2000);
		++stateStep;
		break;

	case 4:
		player1Wins->UpdateCurrentFrame();
		player2Wins->UpdateCurrentFrame();

		if (timer.Reached())
		{
			if (showDrawGame || showDoubleKO)
			{
				stateStep = 8;
			}
			else
			{
				if ((showP1Win && scene->player1->life == 100) ||
					(showP2Win && scene->player2->life == 100))
				{
					showPerfect = true;
					servicesManager->audio->PlayFx(perfectFx);
					timer.SetNewInterval(2000);
					++stateStep;
				}
				else
					stateStep = 6;
			}

			showDoubleKO = false;
			showDrawGame = false;
			showP1Win = false;
			showP2Win = false;
		}
		break;

	case 5:
		perfect.UpdateCurrentFrame();
		if (timer.Reached())
		{
			showPerfect = false;
			++stateStep;
		}
		break;

	case 6:
		showScores = true;
		++stateStep;
		break;

	case 7:
		if (tempScore > 0)
		{
			servicesManager->audio->PlayFx(bonusShortFx);
			if (tempScore > 200)
			{
				bonusScore += 200;
				
				if (scene->winnerPlayer == 1)
				{
					SF2Stats::p1Stats.score += 200;
					
					if (SF2Stats::p1Stats.score > SF2Stats::currentRecord)
						SF2Stats::currentRecord = SF2Stats::p1Stats.score;
				} else if (scene->winnerPlayer == 2)
				{
					SF2Stats::p2Stats.score += 200;
					if (SF2Stats::p2Stats.score > SF2Stats::currentRecord)
						SF2Stats::currentRecord = SF2Stats::p2Stats.score;
				}

				tempScore -= 200;
			}
			else
			{
				bonusScore += tempScore;

				if (scene->winnerPlayer == 1)
				{
					SF2Stats::p1Stats.score += tempScore;
					if (SF2Stats::p1Stats.score > SF2Stats::currentRecord)
						SF2Stats::currentRecord = SF2Stats::p1Stats.score;
				}
				else if (scene->winnerPlayer == 2)
				{
					SF2Stats::p2Stats.score += tempScore;
					if (SF2Stats::p2Stats.score > SF2Stats::currentRecord)
						SF2Stats::currentRecord = SF2Stats::p2Stats.score;
				}

				tempScore = 0;
			}
		}
		else
		{
			servicesManager->audio->PlayFx(bonusFx);
			timer.SetNewInterval(2000);
			++stateStep;
		}
		break;

	case 8:
		if (timer.Reached())
		{
			stateFinished = true;
		}
		break;
	}
	return Result::R_OK;
}

void SceneMatchGUI::DrawScore(unsigned int score, const fPoint& pos, bool bigDigit) const
{
	unsigned int currentScore;
	//Max 6 digits
	if (score > 999999)
		currentScore = 999999;
	else
		currentScore = score;

	fPoint position = pos;
	bool paintZero = false;

	//Hundred thousands
	int digit = (int)currentScore / 100000;
	paintZero = DrawScoreDigit(digit, position, bigDigit, paintZero);

	//Ten thousands
	currentScore %= 100000;
	position.x += 8;
	digit = (int)currentScore / 10000;
	paintZero = DrawScoreDigit(digit, position, bigDigit, paintZero);

	//Thousands
	currentScore %= 10000;
	position.x += 8;
	digit = (int)currentScore / 1000;
	paintZero = DrawScoreDigit(digit, position, bigDigit, paintZero);

	//Hundreds
	currentScore %= 1000;
	position.x += 8;
	digit = (int)currentScore / 100;
	paintZero = DrawScoreDigit(digit, position, bigDigit, paintZero);

	//Tens
	currentScore %= 100;
	position.x += 8;
	digit = (int)currentScore / 10;
	paintZero = DrawScoreDigit(digit, position, bigDigit, paintZero);

	//Units
	currentScore %= 10;
	position.x += 8;
	digit = (int)currentScore;
	DrawScoreDigit(digit, position, bigDigit, true);
}

bool SceneMatchGUI::DrawScoreDigit(int number, const fPoint& pos, bool bigDigit, bool paintZero) const
{
	if (number == 0 && !paintZero)
		return false;

	const Sprite* digit;
	if (bigDigit)
		digit = scoreBigNumbers[number];
	else
		digit = scoreLittleNumbers[number];
	servicesManager->render->BlitGUI(texture, digit->GetRectPosition(pos), digit->rect);

	return true;
}

Entity::Result SceneMatchGUI::DrawCommon() const
{
	//Record score
	if (SF2Stats::currentRecord >= SF2Stats::initialRecord)
	{
		servicesManager->render->BlitGUI(texture, recordScore.GetRectPosition(recordScorePos), recordScore.rect);
		DrawScore(SF2Stats::currentRecord, recordScoreNumberPos);
	}
	else
		servicesManager->render->BlitGUI(texture, originalRecordScore.GetRectPosition(recordScorePos), originalRecordScore.rect);

	//Victories
	switch (scene->player1->roundVictories)
	{
	case 2:
		servicesManager->render->BlitGUI(texture, victory.GetRectPosition(victoryP12Pos), victory.rect);
		//"no break" intended
	case 1:
		servicesManager->render->BlitGUI(texture, victory.GetRectPosition(victoryP11Pos), victory.rect);
	}

	switch (scene->player2->roundVictories)
	{
	case 2:
		servicesManager->render->BlitGUI(texture, victory.GetRectPosition(victoryP22Pos, Direction::LEFT), victory.rect, Direction::LEFT);
		//"no break" intended
	case 1:
		servicesManager->render->BlitGUI(texture, victory.GetRectPosition(victoryP21Pos, Direction::LEFT), victory.rect, Direction::LEFT);
	}

	//Life bar
	servicesManager->render->BlitGUI(texture, lifeBar.GetRectPosition(lifeBarPos), lifeBar.rect);
	servicesManager->render->BlitGUI(texture, redKO.GetFrame().GetRectPosition(redKOPos), redKO.GetFrame().rect);

	servicesManager->render->SetDrawColor(Color(Color::Predefined::YELLOW));
	fRect lifeBar;
	lifeBar.h = 8;
	lifeBar.y = (float)barP1Pos.y;

	int life;
	float shownLife;

	//Bar player 1
	life = scene->player1->life;
	shownLife = scene->player1->shownLife;
	if (life < shownLife)
	{
		shownLife = shownLife + ((life - shownLife) * 10 * servicesManager->time->frameTimeSeconds);
	}
	lifeBar.w = (float)(int)(shownLife * 88 / 100);
	lifeBar.x = (float)(barP1Pos.x - lifeBar.w);
	servicesManager->render->DrawRectFill(lifeBar, true);
	if (shownLife < life + 1) //To avoid infinite calculation
		shownLife = (float)life;
	scene->player1->shownLife = shownLife;

	//Bar player 2
	life = scene->player2->life;
	shownLife = scene->player2->shownLife;
	if (life < shownLife)
	{
		shownLife = shownLife + ((life - shownLife) * 10 * servicesManager->time->frameTimeSeconds);
	}
	lifeBar.w = (float)(int)(shownLife * 88 / 100);
	lifeBar.x = (float)barP2Pos.x;
	servicesManager->render->DrawRectFill(lifeBar, true);
	if (shownLife < life + 1)
		shownLife = (float)life;
	scene->player2->shownLife = shownLife;

	//Time
	if (scene->timeLimit)
	{
		int firstDigit = (int)(scene->time / 10);
		const Animation* firstNumSprite = timeNumbers[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetFrame().GetRectPosition(timeDigit1Pos), firstNumSprite->GetFrame().rect);

		int secondDigit = scene->time % 10;
		const Animation* secondNumSprite = timeNumbers[secondDigit];
		servicesManager->render->BlitGUI(texture, secondNumSprite->GetFrame().GetRectPosition(timeDigit2Pos), secondNumSprite->GetFrame().rect);
	}
	else
	{
		servicesManager->render->BlitGUI(texture, numInf.GetRectPosition(timeDigit1Pos), numInf.rect);
	}

	//Character name
	servicesManager->render->BlitGUI(texture, player1Name->GetRectPosition(player1NamePos), player1Name->rect);
	servicesManager->render->BlitGUI(texture, player2Name->GetRectPosition(player2NamePos), player2Name->rect);

	return Result::R_OK;
}

Entity::Result SceneMatchGUI::DrawIntro() const
{
	//Players score
	servicesManager->render->BlitGUI(texture, p1Score.GetRectPosition(p1ScorePos), p1Score.rect);
	DrawScore(SF2Stats::p1Stats.score, p1ScoreNumberPos);
	servicesManager->render->BlitGUI(texture, p2Score.GetRectPosition(p2ScorePos), p2Score.rect);
	DrawScore(SF2Stats::p2Stats.score, p2ScoreNumberPos);

	if (stateStep > 0)
	{
		servicesManager->render->BlitGUI(texture, currentRoundFight->GetFrame().GetRectPosition(roundFightPos), currentRoundFight->GetFrame().rect);

		servicesManager->render->BlitGUI(texture, battle.GetRectPosition(battlePos), battle.rect);

		int firstDigit = (int)(scene->matchInfo.battleNumber / 10);
		const Sprite* firstNumSprite = battleNumbers[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(battleDigit1Pos), firstNumSprite->rect);

		int secondDigit = scene->matchInfo.battleNumber % 10;
		const Sprite* secondNumSprite = battleNumbers[secondDigit];
		servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(battleDigit2Pos), secondNumSprite->rect);
	}

	return Result::R_OK;
}

Entity::Result SceneMatchGUI::DrawFight() const
{
	//Players score
	servicesManager->render->BlitGUI(texture, p1Score.GetRectPosition(p1ScorePos), p1Score.rect);
	DrawScore(SF2Stats::p1Stats.score, p1ScoreNumberPos);
	servicesManager->render->BlitGUI(texture, p2Score.GetRectPosition(p2ScorePos), p2Score.rect);
	DrawScore(SF2Stats::p2Stats.score, p2ScoreNumberPos);

	return Result::R_OK;
}

Entity::Result SceneMatchGUI::DrawPause() const
{
	servicesManager->render->BlitGUI(texture, pause.GetFrame().GetRectPosition(pause1Pos), pause.GetFrame().rect);
	servicesManager->render->BlitGUI(texture, pause.GetFrame().GetRectPosition(pause2Pos), pause.GetFrame().rect);

	return Result::R_OK;
}

Entity::Result SceneMatchGUI::DrawFinish() const
{
	//Players score
	servicesManager->render->BlitGUI(texture, p1Score.GetRectPosition(p1ScorePos), p1Score.rect);
	DrawScore(SF2Stats::p1Stats.score, p1ScoreNumberPos);
	servicesManager->render->BlitGUI(texture, p2Score.GetRectPosition(p2ScorePos), p2Score.rect);
	DrawScore(SF2Stats::p2Stats.score, p2ScoreNumberPos);

	if(showTimeOver)
		servicesManager->render->BlitGUI(texture, timeOver.GetRectPosition(finishMatcInfoPos), timeOver.rect);

	if(showDrawGame)
		servicesManager->render->BlitGUI(texture, drawGame.GetRectPosition(finishMatcInfoPos), drawGame.rect);

	if (showP1Win)
		servicesManager->render->BlitGUI(texture, player1Wins->GetFrame().GetRectPosition(finishMatcInfoPos), player1Wins->GetFrame().rect);

	if (showP2Win)
		servicesManager->render->BlitGUI(texture, player2Wins->GetFrame().GetRectPosition(finishMatcInfoPos), player2Wins->GetFrame().rect);

	if (showPerfect)
		servicesManager->render->BlitGUI(texture, perfect.GetFrame().GetRectPosition(finishMatcInfoPos), perfect.GetFrame().rect);

	if (showScores) 
	{
		if (scene->timeLimit)
		{
			servicesManager->render->BlitGUI(texture, time.GetRectPosition(timePos), time.rect);
			DrawScore(scene->timeScore, timeScorePos, true);
		}
		servicesManager->render->BlitGUI(texture, vital.GetRectPosition(vitalPos), vital.rect);
		DrawScore(scene->vitalScore, vitalScorePos, true);
		servicesManager->render->BlitGUI(texture, bonus.GetRectPosition(bonusPos), bonus.rect);
		DrawScore(bonusScore, bonusScorePos, true);
	}

	return Result::R_OK;
}

Entity::Result SceneMatchGUI::Draw() const
{
	Entity::Result res = DrawCommon();

	if (res == Entity::Result::R_OK)
	{
		switch (currentState)
		{
		case MatchGUIState::INTRO:
			res = DrawIntro();
			break;

		case MatchGUIState::FIGHT:
			res = DrawFight();
			break;


		case MatchGUIState::PAUSE:
			res = DrawPause();
			break;

		case MatchGUIState::FINISH:
			res = DrawFinish();
			break;
		}
	}

	return res;
}


const Sprite* SceneMatchGUI::LoadSpriteName(int characterId) const
{
	Sprite* spriteName = new Sprite();
	
	switch (characterId)
	{
	case 0:
		config->LoadSprite(*spriteName, configSection, "ryuName");
		break;
	case 1:
		config->LoadSprite(*spriteName, configSection, "hondaName");
		break;
	case 2:
		config->LoadSprite(*spriteName, configSection, "blankaName");
		break;
	case 3:
		config->LoadSprite(*spriteName, configSection, "guileName");
		break;
	case 4:
		config->LoadSprite(*spriteName, configSection, "kenName");
		break;
	case 5:
		config->LoadSprite(*spriteName, configSection, "chunliName");
		break;
	case 6:
		config->LoadSprite(*spriteName, configSection, "zanguiefName");
		break;
	case 7:
		config->LoadSprite(*spriteName, configSection, "dalshimName");
		break;
	}
	return spriteName;
}

Animation* SceneMatchGUI::LoadNameWins(int characterId)
{
	Animation* nameWins = new Animation();

	switch (characterId)
	{
	case 0:
		config->LoadAnimation(*nameWins, configSection, "ryuWins");
		break;
	case 1:
		config->LoadAnimation(*nameWins, configSection, "hondaWins");
		break;
	case 2:
		config->LoadAnimation(*nameWins, configSection, "blankaWins");
		break;
	case 3:
		config->LoadAnimation(*nameWins, configSection, "guileWins");
		break;
	case 4:
		config->LoadAnimation(*nameWins, configSection, "kenWins");
		break;
	case 5:
		config->LoadAnimation(*nameWins, configSection, "chunliWins");
		break;
	case 6:
		config->LoadAnimation(*nameWins, configSection, "zanguiefWins");
		break;
	case 7:
		config->LoadAnimation(*nameWins, configSection, "dalshimWins");
		break;
	}
	return nameWins;
}


