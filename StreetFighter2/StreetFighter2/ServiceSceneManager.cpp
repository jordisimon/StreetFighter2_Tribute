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

bool ServiceSceneManager::Init()
{
	doChangeScene = false;
	return true;
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
	if (doChangeScene)
		ChangeScene();

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


void ServiceSceneManager::ChangeScene()
{
	if (nextScene != nullptr)
	{
		nextScene->Init();
	}

	if (currentScene == nullptr)
	{
		currentScene = nextScene;
		nextScene = nullptr;
		currentScene->Start();
	}
	else
	{
		servicesManager->fade->StartFading(nextScene, currentScene, fadeTime);
	}

	doChangeScene = false;
}

void ServiceSceneManager::SetNewScene(Scene * newScene, float fadeT)
{
	nextScene = newScene;
	fadeTime = fadeT;
	doChangeScene = true;
}
