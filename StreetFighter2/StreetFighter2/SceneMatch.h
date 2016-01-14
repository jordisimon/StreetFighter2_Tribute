#pragma once
#include "Scene.h"
#include "SceneMatchInfo.h"
#include "Timer.h"
#include "Point.h"

class MatchState;
class Stage;
class Character;
class CommandContext;
class SceneMatchGUI;
class Collider;

class SceneMatch: public Scene
{
	friend class MatchStateIntro;
	friend class MatchStateFight;
	friend class MatchStatePause;
	friend class MatchStateFinish;
	friend class SceneMatchGUI;

private:
	SceneMatchInfo matchInfo;
	MatchState* currentState = nullptr;

	SceneMatchGUI* GUI = nullptr;
	CommandContext* commandContextFight = nullptr;
	CommandContext* commandContextPause = nullptr;

	Collider* boxLeftCollider = nullptr;
	Collider* boxRightCollider = nullptr;
	
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
	float gravity;

	unsigned int winnerPlayer;
	unsigned int vitalScore;
	unsigned int timeScore;

	void PauseAllTimers();
	void ResumeAllTimers();

	void CorrectPosition(fPoint& position, float margin);
	void MovePlayers();
	void ApplyForceToPlayers(Character* forcedPlayer, Character* otherPlayer);
	void UpdatePlayersCollidersPosition();
	void CheckPlayerDirection();

	void SetCamXPosition();
	void SetCamYPosition();
	void SetCamPosition() const;
	void SetCollidersPosition();

	void SetNewState(MatchState* state);

	void SceneChange();

public:
	SceneMatch(const SceneMatchInfo& sceneInfo);
	~SceneMatch();

	bool Init();
	bool CleanUp();

	bool Start();
	bool Stop();

	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

