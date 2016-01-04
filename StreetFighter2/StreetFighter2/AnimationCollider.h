#pragma once
#include "Animation.h"
#include "Point.h"
#include "Direction.h"

class ICollitionListener;
class AnimationColliderInfo;
enum class ColliderType; //To be defined in Game specific implementation

class AnimationCollider : public Animation
{
private:
	int previousFrame;

protected:
	void OnReset();

public:
	ICollitionListener* listener;

	std::vector<AnimationColliderInfo*> colliderAnimationList;

	AnimationCollider();
	AnimationCollider(const AnimationCollider& other);
	~AnimationCollider();

	void InitColliders(const fPoint& position, Direction direction = Direction::RIGHT);
	void CleanUpColliders();

	void ResetAnimation();
	void UpdateCurrentFrame(const fPoint& position, Direction direction);

	void DisableCurrentColliderFrame(ColliderType type);
};

