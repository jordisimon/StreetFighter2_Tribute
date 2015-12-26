#pragma once
#include "Stage.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"

class StageHonda : public Stage
{
private:
	Sprite ground;
	fPoint groundPos;

	Sprite background;
	fPoint backgroundPos;

	Sprite pool;
	fPoint poolPos;

	Sprite ceiling;
	fPoint ceilingPos;

	Sprite lamp;
	fPoint lamp1Pos;
	fPoint lamp2Pos;

	Animation water;
	fPoint waterPos;

public:
	StageHonda();
	~StageHonda();

	bool Init();

	Entity::Result UpdateState();
	Entity::Result Draw();
};

