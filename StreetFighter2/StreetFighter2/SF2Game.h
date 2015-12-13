#pragma once
#include "Game.h"

//Testing
class ServiceCommandManager;
class Match;

class SF2Game :	public Game
{
private:
	//Testing 
	Match* match;
	ServiceCommandManager* sCommands;

public:
	SF2Game();
	~SF2Game();

	bool Init();
	bool CleanUp();

	Entity::Result ProcessInput();
	Entity::Result UpdateState();
	Entity::Result Draw();
};

