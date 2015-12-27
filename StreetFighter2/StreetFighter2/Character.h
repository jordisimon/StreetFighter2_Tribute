#pragma once
#include "Entity.h"
#include "Point.h"
#include "Direction.h"
#include "ICollitionListener.h"

class State;
class Collider;
struct SDL_Texture;

class SceneMatch;

class Character : public Entity, public ICollitionListener
{
protected:
	const char* configSection = nullptr;
	SDL_Texture* texture = nullptr;
	State* currentState = nullptr;

public:
	//Common
	SceneMatch* match;
	int playerNumber;
	fPoint position;
	Direction direction;
	unsigned int roundVictories;
	unsigned int life;
	float gravity;

	//Character specific
	int characterId;
	int fSpeed;
	int bSpeed;
	float jumpVSpeed;
	int fJumpHSpeed;
	int bJumpHSpeed;
	float margin;

	Character() {};
	~Character() {};

	bool Init();

	bool Start();
	bool Stop();

	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();

	//Entity::Result Draw();

	void OnCollitionEnter(Collider* colA, Collider* colB) {};
	void OnCollitionExit(Collider* colA, Collider* colB) {};
};

