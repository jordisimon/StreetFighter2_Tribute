#pragma once
#include "CharacterType.h"
#include "StageType.h"


struct SceneMatchInfo
{
	bool twoPlayers;
	unsigned int battleNumber;
	CharacterType player1Type;
	CharacterType player2Type;
	unsigned int player1Handicap;
	unsigned int player2Handicap;
	StageType stageType;
};
