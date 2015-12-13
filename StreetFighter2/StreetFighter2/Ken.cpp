#include "Ken.h"

Ken::Ken()
{
	configSection = "Character_Ken";
}


Ken::~Ken()
{
}

bool Ken::Init(const Config & config)
{
	bool res = Player::Init(config);

	if (res)
	{

	}

	return res;
}