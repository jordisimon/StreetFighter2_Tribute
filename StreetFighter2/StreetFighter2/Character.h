#pragma once
#include "Entity.h"
#include "Point.h"
#include "Sprite.h"
#include "Direction.h"
#include "CharacterType.h"
#include "ICollitionListener.h"
#include "AttackInfo.h"
#include <vector>
#include <deque>
#include "CommandAction.h"
#include "SpecialAction.h"
#include "Timer.h"
#include "AnimationCollider.h"

class CharacterState;
class Particle;
class Collider;
struct SDL_Texture;

class Character : public Entity, public ICollitionListener
{
private:
	CharacterState* nextState = nullptr; //Needed because processing a collition can change the state, but we have to do in the next UpdateState. It will mess the colliders list otherwise

	void StoreActions(std::vector<CommandAction> actions);

	//AnimationCollider* currentAnimation = nullptr;

protected:
	const char* configSection = nullptr;
	SDL_Texture* texture = nullptr;
	CharacterState* currentState = nullptr;
	Sprite shadow;

	void SetNewState(CharacterState* state);

public:
	//Common
	CharacterType type;
	int playerNumber;
	fPoint position;
	fPoint nextPosition;
	Direction direction;
	Direction animDirection; //When jumping over rival or getting hold/thrown player direction could be different form anim direction
	AnimationCollider* currentAnimation = nullptr;
	float updateOverallSpeed;
	float yUpdateControl;
	unsigned int roundVictories;
	int life;
	float shownLife;
	float gravity;
	int groundLevel; //Needed to jump
	bool isAttacking;
	bool isGrabbed;

	float hitBackwardMovement;
	float hitBackwardSpeed;
	float applyBackwardMovementToOtherPlayerRatio;
	unsigned int handicap;

	Character* rival;

	//Special movements control
	std::deque<SpecialAction> actionsSequence;
	Timer actionsSequenceTimer{1000};

	Particle* currentAttackParticle = nullptr; //Character can have only one attack particle at a time (like Hadoken or Sonic boom)

	//Knockdown control
	unsigned int knockdownDamage;
	Timer knockdownTimer{2000};

	//Stunned control
	Particle* particleStunned = nullptr;
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
	static int floorHit2Sfx;

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

	//Common animations (all characters will have)
	AnimationCollider idle;
	AnimationCollider fWalk;
	AnimationCollider bWalk;
	AnimationCollider jump;
	AnimationCollider fJump;
	AnimationCollider bJump;
	AnimationCollider crouch;
	AnimationCollider blocking;
	AnimationCollider cBlocking;
	AnimationCollider lPunch;
	AnimationCollider mPunch;
	AnimationCollider hPunch;
	AnimationCollider flPunch;
	AnimationCollider fmPunch;
	AnimationCollider fhPunch;
	AnimationCollider lKick;
	AnimationCollider mKick;
	AnimationCollider hKick;
	AnimationCollider flKick;
	AnimationCollider fmKick;
	AnimationCollider fhKick;
	AnimationCollider clPunch;
	AnimationCollider cmPunch;
	AnimationCollider chPunch;
	AnimationCollider clKick;
	AnimationCollider cmKick;
	AnimationCollider chKick;
	AnimationCollider jlPunch;
	AnimationCollider jmPunch;
	AnimationCollider jhPunch;
	AnimationCollider jlKick;
	AnimationCollider jmKick;
	AnimationCollider jhKick;
	AnimationCollider fjlPunch;
	AnimationCollider fjmPunch;
	AnimationCollider fjhPunch;
	AnimationCollider fjlKick;
	AnimationCollider fjmKick;
	AnimationCollider fjhKick;
	AnimationCollider grabbed;
	AnimationCollider rolled;
	AnimationCollider rollReleased;
	AnimationCollider hit;
	AnimationCollider faceHit;
	AnimationCollider cHit;
	AnimationCollider aHit;
	AnimationCollider knockdown;
	AnimationCollider knockdownRecover;
	AnimationCollider stunned;
	AnimationCollider KOBegin;
	AnimationCollider KOEnd;
	AnimationCollider victory1;
	AnimationCollider victory2;
	AnimationCollider timeover;

	Character(CharacterType t) : type{ t } {};
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

	void SetDirection(Direction dir);

	void UpdateCurrentAnimation();
	void SetCurrentAnimation(AnimationCollider& anim);
	void SetCurrentAnimation(AnimationCollider& anim, Direction dir);
	void CleanupCurrentAnimationColliders() const;

	void PlaySfx(int sfx) const;

	const AttackInfo GetAttackInfo() const;

	void PauseAllTimers();
	void ResumeAllTimers();

	void SubstractDamage(int damage);

	void ClearActionsSequence();
	virtual CharacterState* CheckSpecialActions() { return nullptr; };
	void UpdateColliders();
	void UpdateYPosition();
	void MoveXPosition(Direction dir, int speed);
	void IfMovingForwardRecalculatePositionWithPressingSpeed();
	void RoundFinished(int playerWin);
	void MatchFinished(int playerWin);

	virtual void Grabbed() {};
	virtual void Thrown() {};

	bool RivalDistanceLowerThan(float minimumDistance);
	bool RivalParticleDistanceLowerThan(float minimumDistance);
};

