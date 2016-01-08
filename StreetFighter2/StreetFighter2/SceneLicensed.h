#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Point.h"
#include "Timer.h"

struct SDL_Texture;

class SceneLicensed : public Scene
{
private:
	const char* configSection;
	SDL_Texture* texture = nullptr;

	Sprite licensed;
	fPoint licensedPos;

	Timer timer;

public:
	SceneLicensed();
	~SceneLicensed();

	bool Init();
	bool CleanUp();

	bool Start();

	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

