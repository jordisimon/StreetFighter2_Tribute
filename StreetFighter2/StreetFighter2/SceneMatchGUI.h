#pragma once
#include "Entity.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"

struct SDL_Texture;
class SceneMatch;

class SceneMatchGUI : public Entity
{
public:
	SceneMatch* scene;
	SDL_Texture* texture = nullptr;

	SceneMatchGUI();
	~SceneMatchGUI();

	bool Init();
	bool CleanUp();

	//virtual bool Start() { return true; }
	//virtual bool Stop() { return true; }

	//virtual bool ProcessInput(CommandData* commandData) { return true; };
	Result UpdateState() { return Result::R_OK; };
	Result Draw();
};

