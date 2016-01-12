#pragma once
#include <vector>
#include "Sprite.h"

class Collider;
enum class ColliderType; //To be defined in Game specific implementation

class AnimationColliderInfo
{
public:
	Collider* collider = nullptr;
	ColliderType type;
	std::vector<Sprite> colliderFrameSprites; //Sprite, not Sprite* intended
	std::vector<bool> colliderFrameActive;
	std::vector<bool> colliderCurrentFrameActive;

	AnimationColliderInfo();
	~AnimationColliderInfo();

	void DisableColliders();
};

