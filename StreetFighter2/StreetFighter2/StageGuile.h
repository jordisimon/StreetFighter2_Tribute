#pragma once
#include "Stage.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"

class StageGuile :	public Stage
{
private:
	Sprite ground;
	fPoint groundPos;

	Sprite background;
	fPoint backgroundPos;

	Sprite plane;
	fPoint planePos;

	Sprite fence;
	fPoint fencePos;

	Animation crowd1;
	fPoint crowd1Pos;
	Animation crowd2;
	fPoint crowd2Pos;

public:
	StageGuile();
	~StageGuile();

	bool Init();
	bool Start();

	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

