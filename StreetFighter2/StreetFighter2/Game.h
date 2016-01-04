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

	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

Game* CreateGame(); //To be defined in Game specific implementation

