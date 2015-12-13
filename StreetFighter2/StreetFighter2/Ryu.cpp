#include "Ryu.h"

Ryu::Ryu()
{
	configSection = "Character_Ryu";
}


Ryu::~Ryu()
{
}

bool Ryu::Init(const Config & config)
{
	bool res = Player::Init(config);

	if (res)
	{

	}

	return res;
}
