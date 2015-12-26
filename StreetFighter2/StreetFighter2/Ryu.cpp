#include "Ryu.h"
#include "Config.h"

Ryu::Ryu()
{
	configSection = "Character_Ryu";
}


Ryu::~Ryu()
{
}

bool Ryu::Init()
{
	bool res = Character::Init();

	if (res)
	{
		/*config->LoadAnimation(idle, configSection, "idle");
		//config->LoadAnimation(idleBodyCol, configSection, "idleBodyCol");
		config->LoadAnimation(fWalk, configSection, "fWalk");
		config->LoadAnimation(bWalk, configSection, "bWalk");
		config->LoadAnimation(jump, configSection, "jump");
		config->LoadAnimation(fJump, configSection, "fJump");
		config->LoadAnimation(bJump, configSection, "bJump");
		config->LoadAnimation(crouch, configSection, "crouch");
		config->LoadAnimation(blocking, configSection, "blocking");
		config->LoadAnimation(cBlocking, configSection, "cBlocking");*/
	}

	return res;
}
