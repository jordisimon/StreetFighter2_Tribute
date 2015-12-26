#include "RyuKen.h"
#include "Defines.h"
#include "Config.h"
#include "RyuKenStateIdle.h"
#include "ServicesManager.h"
#include "ServiceCollition.h"
#include "ColliderType.h"
#include "Collider.h"
#include "Color.h"
#include "ServiceRender.h"

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
		config->LoadAnimationCollider(idle, configSection, "idle");
		config->LoadAnimationCollider(fWalk, configSection, "fWalk");
		config->LoadAnimationCollider(bWalk, configSection, "bWalk");
		config->LoadAnimationCollider(jump, configSection, "jump");
		config->LoadAnimationCollider(fJump, configSection, "fJump");
		config->LoadAnimationCollider(bJump, configSection, "bJump");
		config->LoadAnimationCollider(crouch, configSection, "crouch");
		config->LoadAnimationCollider(blocking, configSection, "blocking");
		config->LoadAnimationCollider(cBlocking, configSection, "cBlocking");
		config->LoadAnimationCollider(lPunch, configSection, "lPunch");
		config->LoadAnimationCollider(mPunch, configSection, "mPunch");
		config->LoadAnimationCollider(hPunch, configSection, "hPunch");
		config->LoadAnimationCollider(flPunch, configSection, "flPunch");
		config->LoadAnimationCollider(fmPunch, configSection, "fmPunch");
		config->LoadAnimationCollider(fhPunch, configSection, "fhPunch");
		config->LoadAnimationCollider(lKick, configSection, "lKick");
		config->LoadAnimationCollider(mKick, configSection, "mKick");
		config->LoadAnimationCollider(hKick, configSection, "hKick");
		config->LoadAnimationCollider(flKick, configSection, "flKick");
		config->LoadAnimationCollider(fmKick, configSection, "fmKick");
		config->LoadAnimationCollider(fhKick, configSection, "fhKick");
		config->LoadAnimationCollider(clPunch, configSection, "clPunch");
		config->LoadAnimationCollider(cmPunch, configSection, "cmPunch");
		config->LoadAnimationCollider(chPunch, configSection, "chPunch");
		config->LoadAnimationCollider(clKick, configSection, "clKick");
		config->LoadAnimationCollider(cmKick, configSection, "cmKick");
		config->LoadAnimationCollider(chKick, configSection, "chKick");

		idle.listener = this;
		fWalk.listener = this;
		bWalk.listener = this;
		jump.listener = this;
		fJump.listener = this;
		bJump.listener = this;
		crouch.listener = this;
		blocking.listener = this;
		cBlocking.listener = this;
		lPunch.listener = this;
		mPunch.listener = this;
		hPunch.listener = this;
		flPunch.listener = this;
		fmPunch.listener = this;
		fhPunch.listener = this;
		lKick.listener = this;
		mKick.listener = this;
		hKick.listener = this;
		flKick.listener = this;
		fmKick.listener = this;
		chKick.listener = this;
		clPunch.listener = this;
		cmPunch.listener = this;
		chPunch.listener = this;
		clKick.listener = this;
		cmKick.listener = this;
		chKick.listener = this;

		currentAnimation = &idle;

		currentState = new RyuKenStateIdle(this);
	}

	return true;
}

bool RyuKen::CleanUp()
{
	bool res = Character::CleanUp();

	RELEASE(currentState);

	return res;
}

bool RyuKen::Start()
{
	bool res = Character::Start();

	if (res)
	{
		idle.InitColliders(position,direction);
		//bodyCollider = servicesManager->collitions->CreateCollider(ColliderType::CHARACTER_BODY, currentBodyColliderAnimation->GetFrame().GetScreenRect(position, direction), this, Color(Color::Predefined::GREEN));
	}

	return res;
}

bool RyuKen::Stop()
{
	bool res = Character::Stop();

	/*if (bodyCollider != nullptr)
	{
		bodyCollider->toDelete = true;
	}

	if (attackCollider != nullptr)
	{
		attackCollider->toDelete = true;
	}*/

	return false;
}


Entity::Result RyuKen::Draw()
{
	servicesManager->render->BlitScene(texture, currentAnimation->GetFrame().GetRectPosition(position, direction), (currentAnimation->GetFrame().rect), 1.0f, direction);

	return Entity::Result::R_OK;
}
