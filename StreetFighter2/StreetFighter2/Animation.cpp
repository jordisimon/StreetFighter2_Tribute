#include "Animation.h"

const Sprite& Animation::GetCurrentFrame()
{
	current_frame += speed;
	if (current_frame >= frames.size())
		current_frame = 0.0f;
	return frames[(int)current_frame];
}

const Sprite& Animation::GetFrame() const
{
	return frames[(int)current_frame];
}

void Animation::ResetAnimation() { current_frame = 0.0f; }

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
