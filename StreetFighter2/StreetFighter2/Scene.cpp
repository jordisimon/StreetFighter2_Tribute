#include "Scene.h"
#include "ServicesManager.h"
#include "ServiceSceneManager.h"


void Scene::HandleSceneChange(Scene * newScene, float fadeT)
{
	if (!changing)
	{
		changing = true;
		servicesManager->scene->SetNewScene(newScene, fadeT);
	}
}

Scene::Scene() : started{ false }
{
}


Scene::~Scene()
{
}

bool Scene::Start()
{
	changing = false;
	started = true;
	return true;
}

bool Scene::Stop()
{
	started = false;
	return true; 
}

bool Scene::IsStarted()
{
	return started;
}
