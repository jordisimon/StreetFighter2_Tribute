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

	Animation sun;
	fPoint sunPos;

	Animation ad;
	fPoint adPos;

public:
	StageHonda();
	~StageHonda();

	bool Init();
	bool Start();

	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

