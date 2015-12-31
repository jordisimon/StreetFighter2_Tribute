#pragma once
#include "Entity.h"

class Game: public Entity
{
protected:
	bool exit;

public:
	Game();
	~Game();

	bool Init();
	bool CleanUp();

	virtual bool UpdateTime() const;
	virtual bool UpdateInput() const;
	Entity::Result PreDraw() const;
	Entity::Result PostDraw() const;

	Entity::Result Update();
};

Game* CreateGame(); //To be defined in Game specific implementation

