#include "StageGuile.h"
#include "ServicesManager.h"
#include "ServiceRender.h"
#include "Config.h"


StageGuile::StageGuile()
{
	configSection = "Stage_Guile";
}


StageGuile::~StageGuile()
{
}

bool StageGuile::Init()
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


		//plane
		config->LoadSprite(plane, configSection, "plane");
		config->LoadfPoint(planePos, configSection, "planePos");

		//fence
		config->LoadSprite(fence, configSection, "fence");
		config->LoadfPoint(fencePos, configSection, "fencePos");

		//crowd
		config->LoadAnimation(crowd1, configSection, "crowd1");
		config->LoadfPoint(crowd1Pos, configSection, "crowd1Pos");
		config->LoadAnimation(crowd2, configSection, "crowd2");
		config->LoadfPoint(crowd2Pos, configSection, "crowd2Pos");
	}

	return res;
}

bool StageGuile::Start()
{
	bool res = Stage::Start();

	if (res)
	{
		crowd1.ResetAnimation();
		crowd2.ResetAnimation();
	}

	return res;
}

Entity::Result StageGuile::UpdateState()
{
	crowd1.UpdateCurrentFrame();
	crowd2.UpdateCurrentFrame();

	return Entity::Result::R_OK;
}

Entity::Result StageGuile::Draw() const
{
	// Draw everything --------------------------------------
	servicesManager->render->BlitScene(texture, backgroundPos, background.rect, 0.43f); //background

	//Plane
	servicesManager->render->BlitScene(texture, planePos, plane.rect, 0.57f);
	//Ground
	servicesManager->render->BlitScene(texture, groundPos, ground.rect); // floor
	//Fence
	servicesManager->render->BlitScene(texture, fencePos, fence.rect, 0.70f);

	//Crowd
	servicesManager->render->BlitScene(texture, crowd1Pos, crowd1.GetFrame().rect, 0.70f);
	servicesManager->render->BlitScene(texture, crowd2Pos, crowd2.GetFrame().rect, 0.70f);

	return Entity::Result::R_OK;
}
