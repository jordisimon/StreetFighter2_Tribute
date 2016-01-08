#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include "Point.h"
#include "Timer.h"

struct SDL_Texture;

class SceneCapcom :	public Scene
{
private:
	const char* configSection;
	SDL_Texture* texture = nullptr;

	unsigned int step;

	Animation capcom;
	fPoint capcomPos;

	Timer timer;

	int capcomSfx;

public:
	SceneCapcom();
	~SceneCapcom();

	bool Init();
	bool CleanUp();

	bool Start();

	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

