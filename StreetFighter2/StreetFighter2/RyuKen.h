#pragma once
#include "Character.h"
#include "CharacterType.h"
#include "AnimationCollider.h"

enum class AttackType
{
	L_PUNCH,
	M_PUNCH,
	H_PUNCH,
	F_L_PUNCH,
	F_M_PUNCH,
	F_H_PUNCH,
	L_KICK,
	M_KICK,
	H_KICK,
	F_L_KICK,
	F_M_KICK,
	F_H_KICK,
	C_L_PUNCH,
	C_M_PUNCH,
	C_H_PUNCH,
	C_L_KICK,
	C_M_KICK,
	C_H_KICK
};


//Ryu and Ken are almost the same
class RyuKen : public Character
{
public:
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
	AnimationCollider shoryuken;
	AnimationCollider kyakuBegin;
	AnimationCollider kyaku;
	AnimationCollider kyakuEnd;
	AnimationCollider hadoken;
	AnimationCollider shoulderToss;
	AnimationCollider backRoll;
	AnimationCollider hit;
	AnimationCollider faceHit;
	AnimationCollider cHit;
	AnimationCollider knockdown;
	AnimationCollider knockdownRecover;
	AnimationCollider stunned;
	AnimationCollider KO;
	AnimationCollider victory1;
	AnimationCollider victory2;
	AnimationCollider timeover;

public:
	AnimationCollider* currentAnimation = nullptr;

	RyuKen(CharacterType type);
	~RyuKen();

	bool Init();
	bool CleanUp();
	bool Start();
	bool Stop();

	Result Draw();
};

