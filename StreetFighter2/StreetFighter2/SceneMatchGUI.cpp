#include "SceneMatchGUI.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"



SceneMatchGUI::SceneMatchGUI()
{
}


SceneMatchGUI::~SceneMatchGUI()
{
}

bool SceneMatchGUI::Init()
{
	texture = servicesManager->textures->Load("Assets\\SpriteSheets\\Stages\\GUI.png");

	return true;
}

bool SceneMatchGUI::CleanUp()
{
	servicesManager->textures->Unload(texture);

	return true;
}

Entity::Result SceneMatchGUI::Draw()
{

	return Result::R_OK;
}
