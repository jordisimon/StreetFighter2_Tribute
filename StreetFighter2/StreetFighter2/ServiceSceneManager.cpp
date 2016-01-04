#include "ServiceSceneManager.h"
#include "Scene.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceFade.h"


ServiceSceneManager::ServiceSceneManager()
{
}


ServiceSceneManager::~ServiceSceneManager()
{
}

bool ServiceSceneManager::CleanUp()
{
	if (nextScene != nullptr)
	{
		nextScene->CleanUp();
		RELEASE(nextScene);
	}

	if (currentScene != nullptr)
	{
		currentScene->CleanUp();
		RELEASE(currentScene);
	}
	return true;
}

Entity::Result ServiceSceneManager::UpdateState()
{
	if (nextScene != nullptr && nextScene->IsStarted())
	{
		if (currentScene != nullptr)
		{
			currentScene->CleanUp();
			RELEASE(currentScene);
		}

		currentScene = nextScene;
		nextScene = nullptr;
	}

	if (currentScene != nullptr && currentScene->IsStarted())
		return currentScene->UpdateState();

	return Entity::Result::R_OK;
}

Entity::Result ServiceSceneManager::Draw() const
{
	if (currentScene != nullptr && currentScene->IsStarted())
		return currentScene->Draw();

	return Entity::Result::R_OK;
}

void ServiceSceneManager::ChangeScene(Scene * newScene, float fadeTime)
{
	if (newScene != nullptr)
	{
		newScene->Init();
	}

	if (currentScene == nullptr)
	{
		currentScene = newScene;
		currentScene->Start();
	}
	else
	{
		nextScene = newScene;

		servicesManager->fade->StartFading(nextScene, currentScene, 2.0f);
	}
}
