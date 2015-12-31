#pragma once
#include "Service.h"
#include "Color.h"

class Scene;

class ServiceFade :	public Service
{
private:
	Color color;
	unsigned int startTime;
	unsigned int totalTime;
	bool fadingOut;

	Scene* sceneOut = nullptr;
	Scene* sceneIn = nullptr;

public:
	ServiceFade();
	~ServiceFade();

	void StartFading(Scene* in, Scene* out = nullptr, float fadeTime = 1.0f);
	void Fade();
};

