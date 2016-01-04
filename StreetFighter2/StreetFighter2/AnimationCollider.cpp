#include "AnimationCollider.h"
#include "Defines.h"
#include "AnimationColliderInfo.h"
#include "ServicesManager.h"
#include "ServiceCollition.h"
#include "Color.h"
#include "Collider.h"


AnimationCollider::AnimationCollider() : previousFrame {-1}
{
}

AnimationCollider::AnimationCollider(const AnimationCollider & other) : Animation{ other }, previousFrame{ -1 }
{
	listener = other.listener;

	//colliderAnimationList contains AnimationColliderInfo pointers, so we need to copy the objects
	for (const auto& info : other.colliderAnimationList)
	{
		AnimationColliderInfo* newInfo = new AnimationColliderInfo( *info );

		colliderAnimationList.push_back(newInfo);
	}
}


AnimationCollider::~AnimationCollider()
{
	for (auto& anim : colliderAnimationList)
	{
		RELEASE(anim);
	}
}

void AnimationCollider::InitColliders(const fPoint& position, Direction direction)
{
	for (auto& colliderAnimation : colliderAnimationList)
	{	
		if (colliderAnimation->collider == nullptr)
		{
			colliderAnimation->collider = servicesManager->collitions->CreateCollider(
				colliderAnimation->type, //type
				colliderAnimation->colliderFrameSprites[valid_frame].GetScreenRect(position, direction), //rect (from current frame)
				listener, //listener
				Color((Color::Predefined)colliderAnimation->type), //color (based on type)
				colliderAnimation->colliderCurrentFrameActive[valid_frame] //active (from current frame)
				);
		}
	}
}

void AnimationCollider::CleanUpColliders()
{
	for (auto& colliderAnimation : colliderAnimationList)
	{
		if (colliderAnimation->collider != nullptr)
		{
			colliderAnimation->collider->toDelete = true;
			colliderAnimation->collider = nullptr;
		}
	}
}

void AnimationCollider::ResetAnimation()
{
	Animation::ResetAnimation();
	previousFrame = -1;
}

void AnimationCollider::UpdateCurrentFrame(const fPoint& position, Direction direction)
{
	Animation::UpdateCurrentFrame();

	for (auto& colliderAnimation : colliderAnimationList)
	{
		if (colliderAnimation->collider != nullptr)
		{
			colliderAnimation->collider->SetRect(colliderAnimation->colliderFrameSprites[valid_frame].GetScreenRect(position, direction));
			colliderAnimation->collider->active = colliderAnimation->colliderCurrentFrameActive[valid_frame];
		}
	}
}

void AnimationCollider::OnReset()
{
	for (auto& colliderAnimation : colliderAnimationList)
	{
		for (unsigned int i = 0; i < colliderAnimation->colliderFrameActive.size(); ++i)
		{
			colliderAnimation->colliderCurrentFrameActive[i] = colliderAnimation->colliderFrameActive[i];
		}
	}
}

void AnimationCollider::DisableCurrentColliderFrame(ColliderType type)
{
	for (auto& colliderAnimation : colliderAnimationList)
	{
		if (colliderAnimation->type == type)
		{
			colliderAnimation->DisableColliders();
		}
	}
}
