#pragma once
#include "Entity.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"
#include "Timer.h"

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

	Sprite lifeBar;
	fPoint lifeBarPos;
	fPoint barP1Pos;
	fPoint barP2Pos;

	Sprite p1Score;
	Sprite p2Score;
	Sprite recordScore;
	Animation pause;
	fPoint p1ScorePos;
	fPoint p2ScorePos;
	fPoint recordScorePos;
	fPoint pause1Pos;
	fPoint pause2Pos;

	Sprite* player1Name;
	Sprite* player2Name;

	Sprite num0;
	Sprite num1;
	Sprite num2;
	Sprite num3;
	Sprite num4;
	Sprite num5;
	Sprite num6;
	Sprite num7;
	Sprite num8;
	Sprite num9;
	Sprite numInf;
	fPoint digit1Pos;
	fPoint digit2Pos;

	Sprite ryuName;
	Sprite hondaName;
	Sprite blankaName;
	Sprite guileName;
	Sprite kenName;
	Sprite chunliName;
	Sprite zanguiefName;
	Sprite dalshimName;
	fPoint namePlayer1Pos;
	fPoint namePlayer2Pos;
	Sprite victory;


	Animation round1;
	Animation round2;
	Animation round3;
	Animation fRound;
	Animation fight;
	Animation* currentRoundFight;
	fPoint roundFightPos;
	int introStep;
	Timer timer;


	Sprite* GetSpriteNum(int number);
	Sprite* GetSpriteName(int characterId);

public:
	SceneMatch* scene;

	SceneMatchGUI();
	~SceneMatchGUI();

	bool Init();
	bool CleanUp();

	bool Start();
	bool Stop();

	Result UpdateState();
	Result Draw();

	void SetMatchGUIState(MatchGUIState state);
};

