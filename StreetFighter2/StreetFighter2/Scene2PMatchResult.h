#pragma once
#include "Scene.h"
#include "Color.h"
#include "Point.h"
#include "Sprite.h"
#include "SceneMatchInfo.h"
#include "PlayerStats.h"
#include <vector>

struct SDL_Texture;
class CommandContext;

class Scene2PMatchResult :	public Scene
{
private:
	SceneMatchInfo matchInfo;

	Color fadeColor;

	const char* configSection;
	SDL_Texture* texture = nullptr;

	static int matchResultSfx;

	CommandContext* commandContextMenu = nullptr;

	Sprite playerStats;
	fPoint playerStatsPos;

	Sprite RyuBigPortrait;
	Sprite HondaBigPortrait;
	Sprite BlankaBigPortrait;
	Sprite GuileBigPortrait;
	Sprite KenBigPortrait;
	Sprite ChunliBigPortrait;
	Sprite ZanguiefBigPortrait;
	Sprite DalshimBigPortrait;

	std::vector<Sprite*> portraits;
	fPoint p1PortraitPos;
	fPoint p2PortraitPos;

	Sprite whiteBig0;
	Sprite whiteBig1;
	Sprite whiteBig2;
	Sprite whiteBig3;
	Sprite whiteBig4;
	Sprite whiteBig5;
	Sprite whiteBig6;
	Sprite whiteBig7;
	Sprite whiteBig8;
	Sprite whiteBig9;
	std::vector<Sprite*> whiteBigNumbers;

	Sprite redBig0;
	Sprite redBig1;
	Sprite redBig2;
	Sprite redBig3;
	Sprite redBig4;
	Sprite redBig5;
	Sprite redBig6;
	Sprite redBig7;
	Sprite redBig8;
	Sprite redBig9;
	std::vector<Sprite*> redBigNumbers;

	fPoint p1FirstNumberPos;
	fPoint p2FirstNumberPos;

	int numberHDistance;
	int numberVDistance;

	fPoint p1TotalFirstNumberPos;
	fPoint p2TotalFirstNumberPos;

	void DrawCharacterStats(const fPoint& firstDigitPos, unsigned int wins, unsigned int draws, unsigned int loses) const;
	void DrawPlayerStats(const fPoint& firstDigitPos, const fPoint& totalsFirstDigitPos, const PlayerStats& playerStats) const;

public:
	Scene2PMatchResult(const SceneMatchInfo& info);
	~Scene2PMatchResult();

	bool Init();
	bool CleanUp();

	bool Start();

	bool ProcessInput(CommandData* commandData);
	Entity::Result Draw() const;
};

