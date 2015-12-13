#include "StageHonda.h"
#include "Game.h"
#include "ServiceRender.h"

StageHonda::StageHonda()
{
	configSection = "Scene_Honda";
}


StageHonda::~StageHonda()
{
}

bool StageHonda::Init(const Config & config)
{
	bool res = Stage::Init(config);

	if (res)
	{
		// ground
		config.LoadSprite(ground, configSection, "ground");
		config.LoadPoint(groundPos, configSection, "groundPos");

		//background
		config.LoadSprite(background, configSection, "background");
		config.LoadPoint(backgroundPos, configSection, "backgroundPos");

		//ceiling
		config.LoadSprite(ceiling, configSection, "ceiling");
		config.LoadPoint(ceilingPos, configSection, "ceilingPos");

		//pool
		config.LoadSprite(pool, configSection, "pool");
		config.LoadPoint(poolPos, configSection, "poolPos");

		//lamp
		config.LoadSprite(lamp, configSection, "lamp");
		config.LoadPoint(lamp1Pos, configSection, "lamp1Pos");
		config.LoadPoint(lamp2Pos, configSection, "lamp2Pos");

		// water animation
		config.LoadAnimation(water, configSection, "water");
		config.LoadPoint(waterPos, configSection, "waterPos");
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
	game->sRender->Blit(texture, groundPos, &ground.rect); // floor
	game->sRender->Blit(texture, backgroundPos, &background.rect, 0.75f); //background
	game->sRender->Blit(texture, ceilingPos, &ceiling.rect, 0.75f); //ceiling
	game->sRender->Blit(texture, poolPos, &pool.rect); //pool
	game->sRender->Blit(texture, waterPos, &water.GetFrame().rect); // pool animation
	game->sRender->Blit(texture, lamp1Pos, &lamp.rect); //lamp1
	game->sRender->Blit(texture, lamp2Pos, &lamp.rect); //lamp2

	return Entity::Result::R_OK;
}
