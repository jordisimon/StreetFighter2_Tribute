#include "AnimationColliderInfo.h"
#include "Defines.h"


AnimationColliderInfo::AnimationColliderInfo()
{
}


AnimationColliderInfo::~AnimationColliderInfo()
{
}

void AnimationColliderInfo::DisableColliders()
{
	for (auto& active : colliderCurrentFrameActive)
	{
		active = false;
	}
}
