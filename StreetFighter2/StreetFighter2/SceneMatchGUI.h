#pragma once
#include "Entity.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"
#include "Timer.h"
#include <vector>

struct SDL_Texture;
class SceneMatch;

class SceneMatchGUI : public Entity
{
public:
	//SceneMatch simplified state machine 
	enum class MatchGUIState
	{
		INTRO,
		FIGHT,
		PAUSE,
		FINISH
	};

private:
	const char* configSection;
	SDL_Texture* texture = nullptr;

	MatchGUIState currentState;
	bool stateFinished;
	int stateStep;

	bool showTimeOver;
	bool showDoubleKO;
	bool showDrawGame;
	bool showP1Win;
	bool showP2Win;
	bool showPerfect;
	bool showScores;

	//Fx sounds
	static int pauseFx;
	static int roundFx;
	static int oneFx;
	static int twoFx;
	static int threeFx;
	static int fourFx;
	static int fightFx;
	static int perfectFx;
	static int bonusShortFx;
	static int bonusFx;

	Sprite lifeBar;
	fPoint lifeBarPos;
	Animation redKO;
	fPoint redKOPos;
	iPoint barP1Pos;
	iPoint barP2Pos;

	Sprite p1Score;
	fPoint p1ScorePos;
	Sprite p2Score;
	fPoint p2ScorePos;
	Sprite recordScore;	
	Sprite originalRecordScore;
	fPoint recordScorePos;
	Animation pause;
	fPoint pause1Pos;
	fPoint pause2Pos;
	fPoint p1ScoreNumberPos;
	fPoint p2ScoreNumberPos;
	fPoint recordScoreNumberPos;

	Animation num0;
	Animation num1;
	Animation num2;
	Animation num3;
	Animation num4;
	Animation num5;
	Animation num6;
	Animation num7;
	Animation num8;
	Animation num9;
	std::vector<Animation*> timeNumbers;
	Sprite numInf;
	fPoint timeDigit1Pos;
	fPoint timeDigit2Pos;

	Sprite numScoreBig0;
	Sprite numScoreBig1;
	Sprite numScoreBig2;
	Sprite numScoreBig3;
	Sprite numScoreBig4;
	Sprite numScoreBig5;
	Sprite numScoreBig6;
	Sprite numScoreBig7;
	Sprite numScoreBig8;
	Sprite numScoreBig9;
	std::vector<Sprite*> scoreBigNumbers;

	Sprite numScoreLittle0;
	Sprite numScoreLittle1;
	Sprite numScoreLittle2;
	Sprite numScoreLittle3;
	Sprite numScoreLittle4;
	Sprite numScoreLittle5;
	Sprite numScoreLittle6;
	Sprite numScoreLittle7;
	Sprite numScoreLittle8;
	Sprite numScoreLittle9;
	std::vector<Sprite*> scoreLittleNumbers;

	Sprite numBattle0;
	Sprite numBattle1;
	Sprite numBattle2;
	Sprite numBattle3;
	Sprite numBattle4;
	Sprite numBattle5;
	Sprite numBattle6;
	Sprite numBattle7;
	Sprite numBattle8;
	Sprite numBattle9;
	std::vector<Sprite*> battleNumbers;

	const Sprite* player1Name;
	fPoint player1NamePos;
	const Sprite* player2Name;
	fPoint player2NamePos;

	Animation* player1Wins;
	Animation* player2Wins;

	Animation perfect;

	Sprite timeOver;
	Sprite drawGame;
	Sprite doubleKO;
	fPoint finishMatcInfoPos;

	Sprite time;
	fPoint timePos;
	fPoint timeScorePos;
	Sprite vital;
	fPoint vitalPos;
	fPoint vitalScorePos;
	Sprite bonus;
	fPoint bonusPos;
	fPoint bonusScorePos;
	unsigned int tempScore;
	unsigned int bonusScore;

	Sprite victory;
	fPoint victoryP11Pos;
	fPoint victoryP12Pos;
	fPoint victoryP21Pos;
	fPoint victoryP22Pos;

	Animation round1;
	Animation round2;
	Animation round3;
	Animation fRound;
	Animation fight;
	Animation* currentRoundFight;
	int currentRoundFx;
	fPoint roundFightPos;

	Sprite battle;
	fPoint battlePos;
	fPoint battleDigit1Pos;
	fPoint battleDigit2Pos;
	
	Timer timer;

	const Sprite* LoadSpriteName(int characterId) const;
	Animation* LoadNameWins(int characterId);

	Result UpdateIntro();
	Result UpdateFight();
	Result UpdatePause();
	Result UpdateFinish();

	void DrawScore(unsigned int score, const fPoint& pos, bool bigDigit = false) const;
	bool DrawScoreDigit(int number, const fPoint& pos, bool bigDigit, bool paintZero) const;
	Result DrawCommon() const;
	Result DrawIntro() const;
	Result DrawFight() const;
	Result DrawPause() const;
	Result DrawFinish() const;

public:
	SceneMatch* scene;

	SceneMatchGUI();
	~SceneMatchGUI();

	bool Init();
	bool CleanUp();

	bool Start();

	void SetMatchGUIState(MatchGUIState state);
	Result UpdateState();
	Result Draw() const;

	bool StateHasFinished() const { return stateFinished; }
};

