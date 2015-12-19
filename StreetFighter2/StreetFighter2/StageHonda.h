#pragma once
#include "Stage.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"

class StageHonda : public Stage
{
private:
	Sprite ground;
	iPoint groundPos;

	Sprite background;
	iPoint backgroundPos;

	Sprite pool;
	iPoint poolPos;

	Sprite ceiling;
	iPoint ceilingPos;

	Sprite lamp;
	iPoint lamp1Pos;
	iPoint lamp2Pos;

	Animation water;
	iPoint waterPos;

public:
	StageHonda();
	~StageHonda();

	bool Init();

	Entity::Result UpdateState();
	Entity::Result Draw();
};

