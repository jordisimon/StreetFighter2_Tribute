#pragma once
#include "Scene.h"
#include "SceneMatchInfo.h"
#include "Timer.h"
#include "Point.h"

class State;
class Stage;
class Character;
class CommandContext;
class SceneMatchGUI;

class SceneMatch: public Scene
{
	friend class MatchStateIntro;
	friend class MatchStateFight;
	friend class MatchStatePause;
	friend class MatchStateFinish;
	friend class SceneMatchGUI;

private:
	SceneMatchGUI* GUI = nullptr;
	CommandContext* commandContextFight = nullptr;
	CommandContext* commandContextPause = nullptr;
	State* currentState = nullptr;
	Stage* stage = nullptr;
	Character* player1 = nullptr;
	Character* player2 = nullptr;
	Timer timer;
	bool timeLimit;
	unsigned int time;
	unsigned int roundNumber;
	bool paused;
	fPoint camPosition;
	float scene25Percent;
	float scene50Percent;
	float scene75Percent;

	//Fx sounds
	static int pauseFx;
	static int roundFx;
	static int oneFx;
	static int twoFx;
	static int threeFx;
	static int fourFx;
	static int fightFx;

	void CheckPlayerLimits();

	void SetCamXPosition();
	void SetCamYPosition();
	void SetCamPosition();

public:
	SceneMatch(const SceneMatchInfo& sceneInfo);
	~SceneMatch();

	bool Init();
	bool CleanUp();

	bool Start();
	bool Stop();

	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();
	Entity::Result Draw();

	int GetGroundPosition();
	float GetMinXPosition();
	float GetMaxXPosition();
};

