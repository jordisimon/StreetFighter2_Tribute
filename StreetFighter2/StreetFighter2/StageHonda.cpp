#include "StageHonda.h"
#include "Game.h"
#include "ModuleRender.h"

#define CONFIG_SECTION "Scene_Honda"

StageHonda::StageHonda()
{
}


StageHonda::~StageHonda()
{
}

bool StageHonda::Init(const Config & config)
{
	spriteSheetName = config.LoadCharValue(CONFIG_SECTION, "spriteSheetName", "honda_stage.png");
	musicName = config.LoadCharValue(CONFIG_SECTION, "music", "honda.ogg");

	// ground
	config.LoadSprite(ground, CONFIG_SECTION, "ground");
	config.LoadPosition(groundPos, CONFIG_SECTION, "ground");

	//background
	config.LoadSprite(background, CONFIG_SECTION, "background");
	config.LoadPosition(backgroundPos, CONFIG_SECTION, "background");

	//ceiling
	config.LoadSprite(ceiling, CONFIG_SECTION, "ceiling");
	config.LoadPosition(ceilingPos, CONFIG_SECTION, "ceiling");

	//pool
	config.LoadSprite(pool, CONFIG_SECTION, "pool");
	config.LoadPosition(poolPos, CONFIG_SECTION, "pool");

	//lamp
	config.LoadSprite(lamp, CONFIG_SECTION, "lamp");
	config.LoadPosition(lamp1Pos, CONFIG_SECTION, "lamp1");
	config.LoadPosition(lamp2Pos, CONFIG_SECTION, "lamp2");

	// water animation
	config.LoadAnimation(water, CONFIG_SECTION, "water");
	config.LoadPosition(waterPos, CONFIG_SECTION, "water");

	return true;
}

Module::Update_result StageHonda::Update()
{
	// Draw everything --------------------------------------
	game->render->Blit(graphics, groundPos.x, groundPos.y, &ground.rect); // floor
	game->render->Blit(graphics, backgroundPos.x, backgroundPos.y, &background.rect, 0.75f); //background
	game->render->Blit(graphics, ceilingPos.x, ceilingPos.y, &ceiling.rect, 0.75f); //ceiling
	game->render->Blit(graphics, poolPos.x, poolPos.y, &pool.rect); //pool
	game->render->Blit(graphics, waterPos.x, waterPos.y, &water.GetCurrentFrame().rect); // pool animation
	game->render->Blit(graphics, lamp1Pos.x, lamp1Pos.y, &lamp.rect); //lamp1
	game->render->Blit(graphics, lamp2Pos.x, lamp2Pos.y, &lamp.rect); //lamp2

	return Module::Update_result::UPDATE_OK;
}
