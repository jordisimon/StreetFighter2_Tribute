#pragma once
#include "Animation.h"

class ICollitionListener;
class AnimationColliderInfo;

class AnimationCollider : public Animation
{
private:
	int previousFrame;

public:
	ICollitionListener* listener;

	std::vector<AnimationColliderInfo*> colliderAnimationList;

	AnimationCollider();
	~AnimationCollider();

	void InitColliders(const fPoint& position, Direction direction = Direction::RIGHT);
	void CleanUpColliders();

	void ResetAnimation();
	void UpdateCurrentFrame(const fPoint& position, Direction direction);
};

