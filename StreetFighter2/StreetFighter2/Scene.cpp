#include "Scene.h"

Scene::Scene() : started{ false }
{
}


Scene::~Scene()
{
}

bool Scene::Start()
{
	started = true;
	return true;
}

bool Scene::Stop()
{
	started = false;
	return true; 
}
