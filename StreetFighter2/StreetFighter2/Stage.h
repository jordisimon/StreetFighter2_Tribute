#pragma once
#include "Entity.h"
#include "Point.h"

struct SDL_Texture;

class Stage : public Entity
{
protected:
	const char* configSection;

public:
	SDL_Texture* texture = nullptr;
	const char* musicName;

	iPoint camMin;
	iPoint camMax;
	iPoint camStart;
	int groundLevel;
	iPoint p1StartPoint;
	iPoint p2StartPoint;

	Stage() {};
	~Stage() {};

	bool Init(const Config& config);

	bool Start();
	bool Stop();
};

