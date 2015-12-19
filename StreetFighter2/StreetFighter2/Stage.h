#pragma once
#include "Entity.h"
#include "Point.h"

struct SDL_Texture;
class Collider;

class Stage : public Entity
{
protected:
	const char* configSection;

public:
	SDL_Texture* texture = nullptr;
	const char* musicName = nullptr;
	Collider* boxCollider = nullptr;

	iPoint camMin;
	iPoint camMax;
	iPoint camStart;
	int groundLevel;
	iPoint p1StartPoint;
	iPoint p2StartPoint;

	Stage() {};
	~Stage() {};

	bool Init();
	bool CleanUp();

	bool Start();
	bool Stop();
};

