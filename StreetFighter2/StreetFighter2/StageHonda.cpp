#include "StageHonda.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "Config.h"

StageHonda::StageHonda()
{
	configSection = "Scene_Honda";
}


StageHonda::~StageHonda()
{
}

bool StageHonda::Init()
{
	bool res = Stage::Init();

	if (res)
	{
		// ground
		config->LoadSprite(ground, configSection, "ground");
		config->LoadfPoint(groundPos, configSection, "groundPos");

		//background
		config->LoadSprite(background, configSection, "background");
		config->LoadfPoint(backgroundPos, configSection, "backgroundPos");

		//ceiling
		config->LoadSprite(ceiling, configSection, "ceiling");
		config->LoadfPoint(ceilingPos, configSection, "ceilingPos");

		//pool
		config->LoadSprite(pool, configSection, "pool");
		config->LoadfPoint(poolPos, configSection, "poolPos");

		//lamp
		config->LoadSprite(lamp, configSection, "lamp");
		config->LoadfPoint(lamp1Pos, configSection, "lamp1Pos");
		config->LoadfPoint(lamp2Pos, configSection, "lamp2Pos");

		// water animation
		config->LoadAnimation(water, configSection, "water");
		config->LoadfPoint(waterPos, configSection, "waterPos");

		// sun animation
		config->LoadAnimation(sun, configSection, "sun");
		config->LoadfPoint(sunPos, configSection, "sunPos");

		// ad animation
		config->LoadAnimation(ad, configSection, "ad");
		config->LoadfPoint(adPos, configSection, "adPos");
	}

	return res;
}

bool StageHonda::Start()
{
	bool res = Stage::Start();

	if (res)
	{
		water.ResetAnimation();
		sun.ResetAnimation();
		ad.ResetAnimation();
	}

	return res;
}

Entity::Result StageHonda::UpdateState()
{
	water.UpdateCurrentFrame();

	if (showFinishAnimations)
	{
		sun.UpdateCurrentFrame();
		ad.UpdateCurrentFrame();
	}

	return Entity::Result::R_OK;
}

Entity::Result StageHonda::Draw() const
{
	// Draw everything --------------------------------------
	servicesManager->render->BlitScene(texture, groundPos, ground.rect); // floor
	servicesManager->render->BlitScene(texture, backgroundPos, background.rect, 0.75f); //background

	if (showFinishAnimations)
	{
		servicesManager->render->BlitScene(texture, sunPos, sun.GetFrame().rect, 0.75f); // sun animation
		servicesManager->render->BlitScene(texture, adPos, ad.GetFrame().rect, 0.75f); // sun animation
	}

	servicesManager->render->BlitScene(texture, ceilingPos, ceiling.rect, 0.75f); //ceiling
	servicesManager->render->BlitScene(texture, poolPos, pool.rect); //pool
	servicesManager->render->BlitScene(texture, waterPos, water.GetFrame().rect); // pool animation
	servicesManager->render->BlitScene(texture, lamp1Pos, lamp.rect); //lamp1
	servicesManager->render->BlitScene(texture, lamp2Pos, lamp.rect); //lamp2

	return Entity::Result::R_OK;
}
