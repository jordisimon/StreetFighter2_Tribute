#pragma once
#include "Service.h"
#include "Entity.h"

class Scene;

class ServiceSceneManager: public Service
{
private:
	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;

	bool doChangeScene;
	float fadeTime;

	void ChangeScene();

public:
	ServiceSceneManager();
	~ServiceSceneManager();

	bool Init();
	bool CleanUp();

	Entity::Result UpdateState();
	Entity::Result Draw() const;

	void SetNewScene(Scene* newScene, float fadeT = 2.0f);
};

