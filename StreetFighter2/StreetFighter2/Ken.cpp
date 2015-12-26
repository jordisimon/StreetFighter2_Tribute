#include "Ken.h"
#include "Config.h"

Ken::Ken()
{
	configSection = "Character_Ken";
}


Ken::~Ken()
{
}

bool Ken::Init()
{
	bool res = Character::Init();

	if (res)
	{
		//config->LoadAnimation(idle, configSection, "idle");
		//config->LoadAnimation(idleBodyCol, configSection, "idleBodyCol");
		//config->LoadAnimation(fWalk, configSection, "fWalk");
		//config->LoadAnimation(bWalk, configSection, "bWalk");
		//config->LoadAnimation(jump, configSection, "jump");
	}

	return res;
}