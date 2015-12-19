#pragma once
#include "Entity.h"

class Game: public Entity
{
protected:
	bool exit;
public:
	Game();
	~Game();

	virtual bool Init();
	bool CleanUp();

	virtual bool UpdateInput();
	Entity::Result PreDraw();
	Entity::Result PostDraw();

	Entity::Result Update();
};

Game* CreateGame(); //To be defined in Game specific implementation

