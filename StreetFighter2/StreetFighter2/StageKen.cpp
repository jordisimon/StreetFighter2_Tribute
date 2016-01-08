#include "StageKen.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "ServiceTime.h"
#include "Config.h"

StageKen::StageKen()
{
	configSection = "Stage_Ken";
}


StageKen::~StageKen()
{
}

bool StageKen::Init()
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

		//flag
		config->LoadAnimation(flag, configSection, "flag");
		config->LoadfPoint(flagPos, configSection, "flagPos");

		//ship
		config->LoadSprite(ship, configSection, "ship");
		config->LoadfPoint(shipPos, configSection, "shipPos");

		//crowd
		config->LoadAnimation(crowd1, configSection, "crowd1");
		config->LoadfPoint(crowd1Pos, configSection, "crowd1Pos");
		config->LoadAnimation(crowd2, configSection, "crowd2");
		config->LoadfPoint(crowd2Pos, configSection, "crowd2Pos");
		config->LoadAnimation(crowd3, configSection, "crowd3");
		config->LoadfPoint(crowd3Pos, configSection, "crowd3Pos");
		config->LoadAnimation(crowd4, configSection, "crowd4");
		config->LoadfPoint(crowd4Pos, configSection, "crowd4Pos");
		config->LoadAnimation(crowd5, configSection, "crowd5");
		config->LoadfPoint(crowd5Pos, configSection, "crowd5Pos");
		config->LoadAnimation(crowd6, configSection, "crowd6");
		config->LoadfPoint(crowd6Pos, configSection, "crowd6Pos");

		//items
		config->LoadSprite(item1, configSection, "item1");
		config->LoadfPoint(item1Pos1, configSection, "item1Pos1");
		config->LoadfPoint(item1Pos2, configSection, "item1Pos2");

		config->LoadSprite(item2, configSection, "item2");
		config->LoadfPoint(item2Pos1, configSection, "item2Pos1");
		config->LoadfPoint(item2Pos2, configSection, "item2Pos2");

		/*//lamp
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
		config->LoadfPoint(adPos, configSection, "adPos");*/
	}

	return res;
}

bool StageKen::Start()
{
	bool res = Stage::Start();

	if (res)
	{
		yShipOffset = 0.0f;
		yShipDirectionDown = true;

		flag.ResetAnimation();
		crowd1.ResetAnimation();
		crowd2.ResetAnimation();
		crowd3.ResetAnimation();
		crowd4.ResetAnimation();
		crowd5.ResetAnimation();
		crowd6.ResetAnimation();
	}

	return res;
}

Entity::Result StageKen::UpdateState()
{
	if (yShipDirectionDown)
	{
		yShipOffset += yShipOffsetDuration * servicesManager->time->frameTimeSeconds;
		if (yShipOffset >= 5.0f)
		{
			yShipDirectionDown = false;
			yShipOffset = 5.0f;
		}
	}
	else
	{
		yShipOffset -= yShipOffsetDuration * servicesManager->time->frameTimeSeconds;
		if (yShipOffset <= 0.0f)
		{
			yShipDirectionDown = true;
			yShipOffset = 0.0f;
		}
	}

	flag.UpdateCurrentFrame();
	crowd1.UpdateCurrentFrame();
	crowd2.UpdateCurrentFrame();
	crowd3.UpdateCurrentFrame();
	crowd4.UpdateCurrentFrame();
	crowd5.UpdateCurrentFrame();
	crowd6.UpdateCurrentFrame();

	return Entity::Result::R_OK;
}

Entity::Result StageKen::Draw() const
{
	// Draw everything --------------------------------------
	servicesManager->render->BlitScene(texture, backgroundPos, background.rect, 0.75f); //background
	servicesManager->render->BlitScene(texture, flagPos, flag.GetFrame().rect, 0.75f); // pool animation

	//Ship
	fPoint itemFinalPos = shipPos;
	itemFinalPos.y += yShipOffset;
	servicesManager->render->BlitScene(texture, itemFinalPos, ship.rect, 0.87f);
	//Crowd
	itemFinalPos = crowd1Pos;
	itemFinalPos.y += yShipOffset;
	servicesManager->render->BlitScene(texture, itemFinalPos, crowd1.GetFrame().rect, 0.87f);
	itemFinalPos = crowd2Pos;
	itemFinalPos.y += yShipOffset;
	servicesManager->render->BlitScene(texture, itemFinalPos, crowd2.GetFrame().rect, 0.87f);
	itemFinalPos = crowd3Pos;
	itemFinalPos.y += yShipOffset;
	servicesManager->render->BlitScene(texture, itemFinalPos, crowd3.GetFrame().rect, 0.87f);
	itemFinalPos = crowd4Pos;
	itemFinalPos.y += yShipOffset;
	servicesManager->render->BlitScene(texture, itemFinalPos, crowd4.GetFrame().rect, 0.87f);
	itemFinalPos = crowd5Pos;
	itemFinalPos.y += yShipOffset;
	servicesManager->render->BlitScene(texture, itemFinalPos, crowd5.GetFrame().rect, 0.87f);
	itemFinalPos = crowd6Pos;
	itemFinalPos.y += yShipOffset;
	servicesManager->render->BlitScene(texture, itemFinalPos, crowd6.GetFrame().rect, 0.87f);


	servicesManager->render->BlitScene(texture, groundPos, ground.rect); // floor
	servicesManager->render->BlitScene(texture, item1Pos1, item1.rect);
	servicesManager->render->BlitScene(texture, item1Pos2, item1.rect);

	return Entity::Result::R_OK;
}

Entity::Result StageKen::DrawForeground() const
{
	servicesManager->render->BlitScene(texture, item2Pos1, item2.rect);
	servicesManager->render->BlitScene(texture, item2Pos2, item2.rect);

	return Entity::Result::R_OK;
}
