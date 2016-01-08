#pragma once
#include "Entity.h"

class Scene : public Entity
{
protected:
	bool started;
	bool changing;

	void HandleSceneChange(Scene* newScene, float fadeT = 2.0f);

public:
	Scene();
	~Scene();

	bool Start();
	bool Stop();

	bool IsStarted();
};

