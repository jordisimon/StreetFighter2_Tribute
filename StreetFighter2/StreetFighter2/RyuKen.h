#pragma once
#include "Character.h"
#include "CharacterType.h"
#include "AnimationCollider.h"
#include "SpecialAction.h"
#include <vector>
#include "RyuKenSpecialAttack.h"

//Ryu and Ken are almost the same
class RyuKen : public Character
{
public:
	//Specific animations
	AnimationCollider shoryukenBegin;
	AnimationCollider shoryuken;
	AnimationCollider shoryukenEnd;
	AnimationCollider kyakuBegin;
	AnimationCollider kyaku;
	AnimationCollider kyakuEnd;
	AnimationCollider hadoken;
	AnimationCollider shoulderToss;
	AnimationCollider backRoll;
	AnimationCollider backRollRecover;

	fPoint hadokenOffset;

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
	static int grabSfx;
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
	RyuKen(CharacterType t);
	~RyuKen();

	bool Init();
	bool CleanUp();
	bool Start();
	bool Stop();

	CharacterState* CheckSpecialActions();
	void Grabbed();
	void Thrown();
};

