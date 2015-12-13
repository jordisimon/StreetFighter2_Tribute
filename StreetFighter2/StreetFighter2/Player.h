#pragma once
#include "Entity.h"
#include "Point.h"
#include "Direction.h"
#include "Animation.h"

class State;
struct SDL_Texture;

class Player : public Entity
{
public:
	State* currentState;

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

	int speed;
	int bSpeed;
	int fJumpDistance;
	int bJumpDistance;

	const char* configSection;

	SDL_Texture* texture = nullptr;

	unsigned int life;
	iPoint position;
	Direction direction;
	Animation* currentAnimation = nullptr;

	Player() {};
	~Player() {};

	bool Init(const Config& config);

	bool Start();
	bool Stop();

	Entity::Result ProcessInput();
	Entity::Result UpdateState();

	Entity::Result Draw();
};

