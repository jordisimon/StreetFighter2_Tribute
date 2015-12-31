#pragma once
#include "Entity.h"
#include "Point.h"
#include "Sprite.h"
#include "Direction.h"
#include "ICollitionListener.h"

class AnimationCollider;
class CharacterState;
class Collider;
struct SDL_Texture;

class Character : public Entity, public ICollitionListener
{
private:
	CharacterState* nextState = nullptr; //Needed because processing a collition can change the state, but we have to do in the next UpdateState. It will mess the colliders list otherwise
	void SetNewState(CharacterState* state);

protected:
	const char* configSection = nullptr;
	SDL_Texture* texture = nullptr;
	CharacterState* currentState = nullptr;
	Sprite shadow;

public:
	//Common
	int playerNumber;
	fPoint position;
	fPoint nextPosition;
	Direction direction;
	unsigned int roundVictories;
	int life;
	float shownLife;
	float gravity;
	int groundLevel; //Needed to jump
	AnimationCollider* currentAnimation = nullptr;
	int currentAttackDamage;
	float hitBackwardMovement;
	float hitBackwardSpeed;
	bool applyToOtherPlayer;

	//Character specific
	int characterId;
	int fSpeed; //Forward speed
	int bSpeed; //Backward speed
	int pSpeed; //Pressing speed
	float jumpVSpeed;
	int fJumpHSpeed;
	int bJumpHSpeed;
	float height;
	float fMargin; //Front margin
	float bMargin; //Back margin


	Character() {};
	~Character() {};

	bool Init();
	bool CleanUp();

	bool Start();
	bool Stop();

	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();

	void DrawShadow(int groundLevel) const;
	Entity::Result Draw() const;

	void OnCollitionEnter(Collider* colA, Collider* colB);
	void OnCollitionExit(Collider* colA, Collider* colB) {};

	void IfMovingForwardRecalculatePositionWithPressingSpeed();
};

