#pragma once
#include "Stage.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"

class StageKen : public Stage
{
private:
	const float yShipOffsetDuration = 3.0f;
	float yShipOffset;
	bool yShipDirectionDown;

	Sprite ground;
	fPoint groundPos;

	Sprite background;
	fPoint backgroundPos;

	Sprite ship;
	fPoint shipPos;

	Animation flag;
	fPoint flagPos;

	Animation crowd1;
	fPoint crowd1Pos;
	Animation crowd2;
	fPoint crowd2Pos;
	Animation crowd3;
	fPoint crowd3Pos;
	Animation crowd4;
	fPoint crowd4Pos;
	Animation crowd5;
	fPoint crowd5Pos;
	Animation crowd6;
	fPoint crowd6Pos;

	Sprite item1;
	fPoint item1Pos1;
	fPoint item1Pos2;

	Sprite item2;
	fPoint item2Pos1;
	fPoint item2Pos2;

public:
	StageKen();
	~StageKen();

	bool Init();
	bool Start();

	Entity::Result UpdateState();
	Entity::Result Draw() const;
	Entity::Result DrawForeground() const;
};

