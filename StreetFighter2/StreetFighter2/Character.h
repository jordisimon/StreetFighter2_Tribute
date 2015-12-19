#pragma once
#include "Entity.h"
#include "Point.h"
#include "Direction.h"
#include "Animation.h"

class State;
struct SDL_Texture;

class Character : public Entity
{
public:
	State* currentState = nullptr;

	//Common animations all characters
	Animation idle;
	Animation fWalk;
	Animation bWalk;
	Animation jump;
	Animation fJump;
	Animation bJump;
	Animation crouch;
	Animation blocking;
	Animation cBlocking;

	int playerNumber;
	int speed;
	int bSpeed;
	int fJumpDistance;
	int bJumpDistance;

	const char* configSection = nullptr;
	SDL_Texture* texture = nullptr;

	unsigned int roundVictories;
	unsigned int life;
	iPoint position;
	Direction direction;
	Animation* currentAnimation = nullptr;

	Character() {};
	~Character() {};

	bool Init();

	bool Start();
	bool Stop();

	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();

	Entity::Result Draw();
};

