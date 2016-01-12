#include "RyuKen.h"
#include "Defines.h"
#include "Config.h"
#include "RyuKenStateIdle.h"
#include "RyuKenStateGrabbed.h"
#include "RyuKenStateKnockdown.h"
#include "ServicesManager.h"
#include "ServiceAudio.h"
#include "Particle.h"

using namespace std;

int RyuKen::lShoryukenSfx = -1;
int RyuKen::mShoryukenSfx = -1;
int RyuKen::hShoryukenSfx = -1;
int RyuKen::lHadokenSfx = -1;
int RyuKen::mHadokenSfx = -1;
int RyuKen::hHadokenSfx = -1;
int RyuKen::lKyakuSfx = -1;
int RyuKen::mKyakuSfx = -1;
int RyuKen::hKyakuSfx = -1;
int RyuKen::grabSfx = -1;
int RyuKen::KOSfx = -1;

const vector<SpecialAction> RyuKen::lightHadokenActions = { SpecialAction::L_PUNCH, SpecialAction::FORWARD, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::mediumHadokenActions = { SpecialAction::M_PUNCH, SpecialAction::FORWARD, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::hardHadokenActions = { SpecialAction::H_PUNCH, SpecialAction::FORWARD, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::lightShoryukenActions = { SpecialAction::L_PUNCH, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN, SpecialAction::FORWARD };
const vector<SpecialAction> RyuKen::mediumShoryukenActions = { SpecialAction::M_PUNCH, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN, SpecialAction::FORWARD };
const vector<SpecialAction> RyuKen::hardShoryukenActions = { SpecialAction::H_PUNCH, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN, SpecialAction::FORWARD };
const vector<SpecialAction> RyuKen::lightKyakuActions = { SpecialAction::L_KICK, SpecialAction::BACKWARD, SpecialAction::DOWN_BACKWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::mediumKyakuActions = { SpecialAction::M_KICK, SpecialAction::BACKWARD, SpecialAction::DOWN_BACKWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::hardKyakuActions = { SpecialAction::H_KICK, SpecialAction::BACKWARD, SpecialAction::DOWN_BACKWARD, SpecialAction::DOWN };

//Testing (specials done with single button)
//const vector<SpecialAction> RyuKen::lightHadokenActions = { SpecialAction::L_PUNCH };
//const vector<SpecialAction> RyuKen::mediumHadokenActions = { SpecialAction::M_PUNCH };
//const vector<SpecialAction> RyuKen::hardHadokenActions = { SpecialAction::H_PUNCH };
//const vector<SpecialAction> RyuKen::lightShoryukenActions = { SpecialAction::L_PUNCH };
//const vector<SpecialAction> RyuKen::mediumShoryukenActions = { SpecialAction::M_PUNCH };
//const vector<SpecialAction> RyuKen::hardShoryukenActions = { SpecialAction::H_PUNCH };
//const vector<SpecialAction> RyuKen::lightKyakuActions = { SpecialAction::L_KICK, SpecialAction::BACKWARD };
//const vector<SpecialAction> RyuKen::mediumKyakuActions = { SpecialAction::M_KICK, SpecialAction::BACKWARD };
//const vector<SpecialAction> RyuKen::hardKyakuActions = { SpecialAction::H_KICK, SpecialAction::BACKWARD };

RyuKen::RyuKen(CharacterType t) : Character{ t }
{
	switch (type)
	{
	case CharacterType::RYU:
		configSection = "Character_Ryu";
		break;
	case CharacterType::KEN:
		configSection = "Character_Ken";
		break;
	}
}


RyuKen::~RyuKen()
{
}

bool RyuKen::Init()
{
	bool res = Character::Init();

	if (res)
	{
		//Attack (special)
		config->LoadAnimationCollider(shoryukenBegin, configSection, "shoryukenBegin");
		shoryukenBegin.listener = this;
		config->LoadAnimationCollider(shoryuken, configSection, "shoryuken");
		shoryuken.listener = this;
		config->LoadAnimationCollider(shoryukenEnd, configSection, "shoryukenEnd");
		shoryukenEnd.listener = this;

		config->LoadAnimationCollider(kyakuBegin, configSection, "kyakuBegin");
		kyakuBegin.listener = this;
		config->LoadAnimationCollider(kyaku, configSection, "kyaku");
		kyaku.listener = this;
		config->LoadAnimationCollider(kyakuEnd, configSection, "kyakuEnd");
		kyakuEnd.listener = this;

		config->LoadAnimationCollider(hadoken, configSection, "hadoken");
		hadoken.listener = this;
		config->LoadfPoint(hadokenOffset, configSection, "hadokenOffset");

		config->LoadAnimationCollider(shoulderToss, configSection, "shoulderToss");
		shoulderToss.listener = this;
		config->LoadAnimationCollider(backRoll, configSection, "backRoll");
		backRoll.listener = this;
		config->LoadAnimationCollider(backRollRecover, configSection, "backRollRecover");
		backRollRecover.listener = this;

		config->LoadAnimationCollider(grabbed, configSection, "grabbed");
		grabbed.listener = this;

		if (lShoryukenSfx == -1) lShoryukenSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\lShoryuken.ogg");
		if (mShoryukenSfx == -1) mShoryukenSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\mShoryuken.ogg");
		if (hShoryukenSfx == -1) hShoryukenSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\hShoryuken.ogg");
		if (lHadokenSfx == -1) lHadokenSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\lHadoken.ogg");
		if (mHadokenSfx == -1) mHadokenSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\mHadoken.ogg");
		if (hHadokenSfx == -1) hHadokenSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\hHadoken.ogg");
		if (lKyakuSfx == -1) lKyakuSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\lKyaku.ogg");
		if (mKyakuSfx == -1) mKyakuSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\mKyaku.ogg");
		if (hKyakuSfx == -1) hKyakuSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\hKyaku.ogg");
		if (grabSfx == -1) grabSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\grab.ogg");
		if (KOSfx == -1) KOSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\KO.ogg");
	}

	return res;
}

bool RyuKen::CleanUp()
{
	bool res = Character::CleanUp();

	return res;
}

bool RyuKen::Start()
{
	bool res = Character::Start();

	if (res)
	{
		RELEASE(currentState);
		currentState = new RyuKenStateIdle(this);
		currentState->OnEnter();
	}

	return res;
}

bool RyuKen::Stop()
{
	bool res = Character::Stop();

	if (currentState != nullptr)
		currentState->OnExit();

	RELEASE(currentState);

	return res;
}

CharacterState * RyuKen::CheckSpecial(const std::vector<SpecialAction>& specialAction, const RyuKenSpecialAttack& type)
{
	bool match;

	match = true;
	vector<SpecialAction>::const_iterator special = specialAction.cbegin();
	deque<SpecialAction>::const_iterator actions = actionsSequence.cbegin();
	while (match && special != specialAction.cend())
	{
		if (actions == actionsSequence.cend())
			match = false;
		else
		{
			match &= (*special) == (*actions);
			++special;
			++actions;
		}
	}

	if (match)
	{
		return currentState->DoSpecialAction(type);
	}

	return nullptr;
}

CharacterState * RyuKen::CheckSpecialActions()
{
	CharacterState* result = nullptr;

	//Hadoken
	if (currentAttackParticle != nullptr)
	{
		//Hadoken sets itself to delete when goes outside camera so we have the next tick to detect it and set this variable to nullptr before particle is released in next particles update
		if (currentAttackParticle->toDelete)
			currentAttackParticle = nullptr;
	}

	if (currentAttackParticle == nullptr)
	{
		result = CheckSpecial(lightHadokenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::L_HADOKEN));
		if (result == nullptr)
			result = CheckSpecial(mediumHadokenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::M_HADOKEN));
		if (result == nullptr)
			result = CheckSpecial(hardHadokenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::H_HADOKEN));
	}

	//Shoryuken
	if (result == nullptr)
		result = CheckSpecial(lightShoryukenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::L_SHORYUKEN));
	if (result == nullptr)
		result = CheckSpecial(mediumShoryukenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::M_SHORYUKEN));
	if (result == nullptr)
		result = CheckSpecial(hardShoryukenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::H_SHORYUKEN));

	//Kyaku
	if (result == nullptr)
		result = CheckSpecial(lightKyakuActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::L_KYAKU));
	if (result == nullptr)
		result = CheckSpecial(mediumKyakuActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::M_KYAKU));
	if (result == nullptr)
		result = CheckSpecial(hardKyakuActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::H_KYAKU));

	return result;
}

void RyuKen::Grabbed()
{
	SetNewState(new RyuKenStateGrabbed(this, direction));
}

void RyuKen::Thrown()
{
	if (direction == Direction::LEFT)
		SetNewState(new RyuKenStateKnockdown(this, Direction::RIGHT));
	else
		SetNewState(new RyuKenStateKnockdown(this, Direction::LEFT));
}
