#pragma once
#include "Entity.h"

class Stage;
class Player;
//class Hud;
//class MatchState;

class Match: public Entity
{
private:
	//MatchState* currentState;
	Stage* stage;
	Player* player1;
	Player* player2;
	//Hud* hud;

public:
	Match();
	~Match();

	bool Init(const Config& config);
	bool CleanUp();

	bool Start();
	bool Stop();

	Entity::Result ProcessInput();
	Entity::Result UpdateState();
	Entity::Result Draw();
};

