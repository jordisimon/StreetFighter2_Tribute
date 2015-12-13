#pragma once
#include "Player.h"
class Ken : public Player
{
public:
	Ken();
	~Ken();

	bool Init(const Config& config);
};

