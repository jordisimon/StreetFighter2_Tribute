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
		config->LoadPoint(groundPos, configSection, "groundPos");

		//background
		config->LoadSprite(background, configSection, "background");
		config->LoadPoint(backgroundPos, configSection, "backgroundPos");

		//ceiling
		config->LoadSprite(ceiling, configSection, "ceiling");
		config->LoadPoint(ceilingPos, configSection, "ceilingPos");

		//pool
		config->LoadSprite(pool, configSection, "pool");
		config->LoadPoint(poolPos, configSection, "poolPos");

		//lamp
		config->LoadSprite(lamp, configSection, "lamp");
		config->LoadPoint(lamp1Pos, configSection, "lamp1Pos");
		config->LoadPoint(lamp2Pos, configSection, "lamp2Pos");

		// water animation
		config->LoadAnimation(water, configSection, "water");
		config->LoadPoint(waterPos, configSection, "waterPos");
	}

	return res;
}

Entity::Result StageHonda::UpdateState()
{
	water.UpdateCurrentFrame();
	return Entity::Result::R_OK;
}

Entity::Result StageHonda::Draw()
{
	// Draw everything --------------------------------------
	servicesManager->render->Blit(texture, groundPos, &ground.rect); // floor
	servicesManager->render->Blit(texture, backgroundPos, &background.rect, 0.75f); //background
	servicesManager->render->Blit(texture, ceilingPos, &ceiling.rect, 0.75f); //ceiling
	servicesManager->render->Blit(texture, poolPos, &pool.rect); //pool
	servicesManager->render->Blit(texture, waterPos, &water.GetFrame().rect); // pool animation
	servicesManager->render->Blit(texture, lamp1Pos, &lamp.rect); //lamp1
	servicesManager->render->Blit(texture, lamp2Pos, &lamp.rect); //lamp2

	return Entity::Result::R_OK;
}
