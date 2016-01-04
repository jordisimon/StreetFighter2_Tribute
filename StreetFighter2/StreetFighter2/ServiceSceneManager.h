#pragma once
#include "Service.h"
#include "Entity.h"

class Scene;

class ServiceSceneManager: public Service
{
private:
	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;

public:
	ServiceSceneManager();
	~ServiceSceneManager();

	bool CleanUp();

	Entity::Result UpdateState();
	Entity::Result Draw() const;

	void ChangeScene(Scene* newScene, float fadeTime = 2.0f);
};

