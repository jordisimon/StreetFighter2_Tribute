#pragma once
#include "Player.h"
class Ryu :	public Player
{
public:
	Ryu();
	~Ryu();

	bool Init(const Config& config);
};

