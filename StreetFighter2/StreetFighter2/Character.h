#pragma once
#include "Entity.h"
#include "Point.h"
#include "Sprite.h"
#include "Direction.h"
#include "ICollitionListener.h"
#include "AttackInfo.h"
#include <vector>
#include <deque>
#include "CommandAction.h"
#include "SpecialAction.h"
#include "Timer.h"

class AnimationCollider;
class CharacterState;
class Particle;
class Collider;
struct SDL_Texture;

class Character : public Entity, public ICollitionListener
{
private:
	CharacterState* nextState = nullptr; //Needed because processing a collition can change the state, but we have to do in the next UpdateState. It will mess the colliders list otherwise
	void SetNewState(CharacterState* state);

	void StoreActions(std::vector<CommandAction> actions);

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
	float updateOverallSpeed;
	float yUpdateControl;
	unsigned int roundVictories;
	int life;
	float shownLife;
	float gravity;
	int groundLevel; //Needed to jump
	AnimationCollider* currentAnimation = nullptr;
	bool isAttacking;
	bool isRivalAttacking;
	float rivalDistance;
	float hitBackwardMovement;
	float hitBackwardSpeed;
	bool applyToOtherPlayer;
	unsigned int handicap;

	//Special movements control
	std::deque<SpecialAction> actionsSequence;
	Timer actionsSequenceTimer{1000};

	//Knockdown control
	unsigned int knockdownDamage;
	Timer knockdownTimer{2000};

	//Stunned control
	Particle* particleStunned;
	Timer stunnedTimer{3000};

	//Fx sounds
	static int lAttackSfx;
	static int mAttackSfx;
	static int hAttackSfx;
	static int lHitSfx;
	static int mHitSfx;
	static int hHitSfx;
	static int hitBlockedSfx;
	static int floorHitSfx;

	//Character specific
	int characterId;
	int fSpeed; //Forward speed
	int bSpeed; //Backward speed
	int pSpeed; //Pressing speed
	float jumpVSpeed;
	float currentJumpSpeed;
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

	void PlaySfx(int sfx) const;

	const AttackInfo GetAttackInfo() const;

	void PauseAllTimers();
	void ResumeAllTimers();

	void ClearActionsSequence();
	virtual CharacterState* CheckSpecialActions() { return nullptr; };
	void UpdateYPosition();
	void MoveXPosition(Direction dir, int speed);
	void IfMovingForwardRecalculatePositionWithPressingSpeed();
	void RoundFinished(int playerWin);
	void MatchFinished(int playerWin);
};

