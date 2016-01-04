#pragma once
#include "Character.h"
#include "CharacterType.h"
#include "AnimationCollider.h"
#include "SpecialAction.h"
#include <vector>
#include "RyuKenSpecialAttack.h"

class Particle;

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
	AnimationCollider shoryukenBegin;
	AnimationCollider shoryuken;
	AnimationCollider shoryukenEnd;
	AnimationCollider kyakuBegin;
	AnimationCollider kyaku;
	AnimationCollider kyakuEnd;
	AnimationCollider hadoken;
	AnimationCollider shoulderToss;
	AnimationCollider backRoll;
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

	fPoint hadokenOffset;
	Particle* currentHadoken;

	//Fx sounds
	static int lShoryukenSfx;
	static int mShoryukenSfx;
	static int hShoryukenSfx;
	static int lHadokenSfx;
	static int mHadokenSfx;
	static int hHadokenSfx;
	static int lKyakuSfx;
	static int mKyakuSfx;
	static int hKyakuSfx;
	static int KOSfx;

	//Special attacks
	static const std::vector<SpecialAction> lightHadokenActions;
	static const std::vector<SpecialAction> mediumHadokenActions;
	static const std::vector<SpecialAction> hardHadokenActions;
	static const std::vector<SpecialAction> lightShoryukenActions;
	static const std::vector<SpecialAction> mediumShoryukenActions;
	static const std::vector<SpecialAction> hardShoryukenActions;
	static const std::vector<SpecialAction> lightKyakuActions;
	static const std::vector<SpecialAction> mediumKyakuActions;
	static const std::vector<SpecialAction> hardKyakuActions;

	CharacterState* CheckSpecial(const std::vector<SpecialAction>& special, const RyuKenSpecialAttack& type);
public:
	RyuKen(CharacterType type);
	~RyuKen();

	bool Init();
	bool CleanUp();
	bool Start();
	bool Stop();

	CharacterState* CheckSpecialActions();
};

