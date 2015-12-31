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

	fPoint camMin;
	fPoint camMax;
	fPoint camStart;
	int groundLevel;
	fPoint p1StartPoint;
	fPoint p2StartPoint;

	bool showFinishAnimations;

	Stage() {};
	~Stage() {};

	bool Init();
	bool CleanUp();

	bool Start();

	void StartFinishAnimations() { showFinishAnimations = true; };
};

