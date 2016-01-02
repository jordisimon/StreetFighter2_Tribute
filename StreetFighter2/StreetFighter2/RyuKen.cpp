#include "RyuKen.h"
#include "Defines.h"
#include "Config.h"
#include "RyuKenStateIdle.h"
#include "ServicesManager.h"
#include "ServiceAudio.h"

using namespace std;

int RyuKen::attackSfx = -1;
int RyuKen::shoryukenSfx = -1;

const vector<SpecialAction> RyuKen::lightHadokenActions = { SpecialAction::L_PUNCH, SpecialAction::FORWARD, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::mediumHadokenActions = { SpecialAction::M_PUNCH, SpecialAction::FORWARD, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::hardHadokenActions = { SpecialAction::H_PUNCH, SpecialAction::FORWARD, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN };
//const vector<SpecialAction> RyuKen::lightShoryukenActions = { SpecialAction::L_PUNCH, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN, SpecialAction::FORWARD };
//const vector<SpecialAction> RyuKen::mediumShoryukenActions = { SpecialAction::M_PUNCH, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN, SpecialAction::FORWARD };
//const vector<SpecialAction> RyuKen::hardShoryukenActions = { SpecialAction::H_PUNCH, SpecialAction::DOWN_FORWARD, SpecialAction::DOWN, SpecialAction::FORWARD };
const vector<SpecialAction> RyuKen::lightKyakuActions = { SpecialAction::L_KICK, SpecialAction::BACKWARD, SpecialAction::DOWN_BACKWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::mediumKyakuActions = { SpecialAction::M_KICK, SpecialAction::BACKWARD, SpecialAction::DOWN_BACKWARD, SpecialAction::DOWN };
const vector<SpecialAction> RyuKen::hardKyakuActions = { SpecialAction::H_KICK, SpecialAction::BACKWARD, SpecialAction::DOWN_BACKWARD, SpecialAction::DOWN };

const vector<SpecialAction> RyuKen::lightShoryukenActions = { SpecialAction::L_PUNCH };
const vector<SpecialAction> RyuKen::mediumShoryukenActions = { SpecialAction::M_PUNCH };
const vector<SpecialAction> RyuKen::hardShoryukenActions = { SpecialAction::H_PUNCH };

RyuKen::RyuKen(CharacterType type)
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
		//Moving
		config->LoadAnimationCollider(idle, configSection, "idle");
		idle.listener = this;
		config->LoadAnimationCollider(fWalk, configSection, "fWalk");
		fWalk.listener = this;
		config->LoadAnimationCollider(bWalk, configSection, "bWalk");
		bWalk.listener = this;
		config->LoadAnimationCollider(jump, configSection, "jump");
		jump.listener = this;
		config->LoadAnimationCollider(fJump, configSection, "fJump");
		fJump.listener = this;
		config->LoadAnimationCollider(bJump, configSection, "bJump");
		bJump.listener = this;
		config->LoadAnimationCollider(crouch, configSection, "crouch");
		crouch.listener = this;
		config->LoadAnimationCollider(blocking, configSection, "blocking");
		blocking.listener = this;
		config->LoadAnimationCollider(cBlocking, configSection, "cBlocking");
		cBlocking.listener = this;

		//Hit
		config->LoadAnimationCollider(hit, configSection, "hit");
		hit.listener = this;
		config->LoadAnimationCollider(faceHit, configSection, "faceHit");
		faceHit.listener = this;
		config->LoadAnimationCollider(cHit, configSection, "cHit");
		cHit.listener = this;
		config->LoadAnimationCollider(aHit, configSection, "aHit");
		aHit.listener = this;

		//Attack (punch)
		//Standing
		config->LoadAnimationCollider(lPunch, configSection, "lPunch");
		lPunch.listener = this;
		config->LoadAnimationCollider(mPunch, configSection, "mPunch");
		mPunch.listener = this;
		config->LoadAnimationCollider(hPunch, configSection, "hPunch");	
		hPunch.listener = this;

		//Close range
		config->LoadAnimationCollider(flPunch, configSection, "flPunch");
		flPunch.listener = this;
		config->LoadAnimationCollider(fmPunch, configSection, "fmPunch");
		fmPunch.listener = this;
		config->LoadAnimationCollider(fhPunch, configSection, "fhPunch");	
		fhPunch.listener = this;

		//Crouching
		config->LoadAnimationCollider(clPunch, configSection, "clPunch");
		clPunch.listener = this;
		config->LoadAnimationCollider(cmPunch, configSection, "cmPunch");
		cmPunch.listener = this;
		config->LoadAnimationCollider(chPunch, configSection, "chPunch");
		chPunch.listener = this;

		//Straight jump
		config->LoadAnimationCollider(jlPunch, configSection, "jlPunch");
		jlPunch.listener = this;
		config->LoadAnimationCollider(jmPunch, configSection, "jmPunch");
		jmPunch.listener = this;
		config->LoadAnimationCollider(jhPunch, configSection, "jhPunch");
		jhPunch.listener = this;
		
		//Diagonal jump
		//Not bug SNES anims are the same as straigh jump
		config->LoadAnimationCollider(fjlPunch, configSection, "jlPunch");
		fjlPunch.listener = this;
		config->LoadAnimationCollider(fjmPunch, configSection, "jmPunch");
		fjmPunch.listener = this;
		config->LoadAnimationCollider(fjhPunch, configSection, "jhPunch");
		fjhPunch.listener = this;

		//Attack (kick)
		//Standing
		config->LoadAnimationCollider(lKick, configSection, "lKick");
		lKick.listener = this;
		config->LoadAnimationCollider(mKick, configSection, "mKick");
		mKick.listener = this;
		config->LoadAnimationCollider(hKick, configSection, "hKick");
		hKick.listener = this;

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

		//Close range
		config->LoadAnimationCollider(flKick, configSection, "flKick");
		flKick.listener = this;
		config->LoadAnimationCollider(fmKick, configSection, "fmKick");
		fmKick.listener = this;
		config->LoadAnimationCollider(fhKick, configSection, "fhKick");
		fhKick.listener = this;
		
		//Crouching
		config->LoadAnimationCollider(clKick, configSection, "clKick");
		clKick.listener = this;
		config->LoadAnimationCollider(cmKick, configSection, "cmKick");
		cmKick.listener = this;
		config->LoadAnimationCollider(chKick, configSection, "chKick");
		chKick.listener = this;

		//Straight jump
		config->LoadAnimationCollider(jlKick, configSection, "jlKick");
		jlKick.listener = this;
		config->LoadAnimationCollider(jmKick, configSection, "jmKick");
		jmKick.listener = this;
		config->LoadAnimationCollider(jhKick, configSection, "jhKick");
		jhKick.listener = this;
		
		//Diagonal jump
		config->LoadAnimationCollider(fjlKick, configSection, "fjlKick");
		fjlKick.listener = this;
		config->LoadAnimationCollider(fjmKick, configSection, "fjmKick");
		fjmKick.listener = this;
		config->LoadAnimationCollider(fjhKick, configSection, "fjhKick");
		fjhKick.listener = this;

		//Finish
		config->LoadAnimationCollider(KOBegin, configSection, "KOBegin");
		KOBegin.listener = this;
		config->LoadAnimationCollider(KOEnd, configSection, "KOEnd");
		KOEnd.listener = this;
		config->LoadAnimationCollider(victory1, configSection, "victory1");
		victory1.listener = this;
		config->LoadAnimationCollider(victory2, configSection, "victory2");
		victory2.listener = this;
		config->LoadAnimationCollider(timeover, configSection, "timeover");
		timeover.listener = this;

		if (attackSfx == -1) attackSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Attack.ogg");
		if (shoryukenSfx == -1) shoryukenSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Voices\\RyuKen\\Shoryuken.ogg");
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

void RyuKen::PlaySfx(int sfx) const
{
	servicesManager->audio->PlayFx(sfx);
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
	CharacterState* result;

	//Hadoken
	result = CheckSpecial(lightHadokenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::L_HADOKEN));
	if(result == nullptr)
		result = CheckSpecial(mediumHadokenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::M_HADOKEN));
	if (result == nullptr)
		result = CheckSpecial(hardHadokenActions, RyuKenSpecialAttack(RyuKenSpecialAttackType::H_HADOKEN));

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
