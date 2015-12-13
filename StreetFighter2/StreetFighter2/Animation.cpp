#include "Animation.h"

Animation::Animation() : frames{}, speed{ 1.0f }, current_frame{ 0.0f }, loop{ true }, emptySprite({ 0,0,0,0 }, { 0,0 })
{
}

Animation::~Animation()
{
}

void Animation::ResetAnimation() { current_frame = 0.0f; }

void Animation::UpdateCurrentFrame()
{
	if (loop)
	{
		current_frame += speed;
		if (current_frame >= frames.size())
			current_frame = 0.0f;
	}
	else
	{
		if (current_frame <= frames.size())
			current_frame += speed;
	}
}

bool Animation::HasFinished() const
{
	return (!loop && current_frame >= frames.size());
}

const Sprite& Animation::GetFrame() const
{
	if (current_frame < frames.size())
		return frames[(int)current_frame];
	else
		return emptySprite;
}

void Animation::NextFrame()
{
	current_frame += 1.0f;
	if (current_frame >= frames.size())
		current_frame = 0.0f;
}

void Animation::PriorFrame()
{
	current_frame -= 1.0f;
	if (current_frame < 0.0f)
		current_frame = frames.size() - 1.0f;
}
