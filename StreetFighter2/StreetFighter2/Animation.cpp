#include "Animation.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTime.h"

Animation::Animation() : frames{}, speed{ 1.0f }, current_frame{ 0.0f }, loop{ true }, forward{true}
{
}

Animation::~Animation()
{
}

void Animation::SetFramesSize()
{
	framesSize = frames.size();
}

void Animation::SetSpeed(float sp)
{
	speed = sp * frames.size();
}

void Animation::SetDuration(float dur)
{
	speed = (1 / dur) * frames.size();
}

void Animation::ResetAnimation()
{ 
	if (forward)
		current_frame = 0.0f;
	else
		current_frame = (float)framesSize - 1;

	valid_frame = (int)current_frame;

	OnReset();
}

void Animation::UpdateCurrentFrame()
{
	if (loop)
	{
		if (forward)
		{
			current_frame += speed * servicesManager->time->frameTimeSeconds;
			if (current_frame >= framesSize)
			{
				current_frame = 0.0f;
				OnReset();
			}
		}
		else
		{
			current_frame -= speed * servicesManager->time->frameTimeSeconds;
			if (current_frame < 0.0f)
			{
				current_frame = (float)framesSize - 1;
				OnReset();
			}
		}
		valid_frame = (int)current_frame;
	}
	else
	{
		if (forward)
		{
			if (current_frame <= framesSize)
				current_frame += speed * servicesManager->time->frameTimeSeconds;

			if (current_frame < framesSize)
				valid_frame = (int)current_frame;
			else
				valid_frame = framesSize - 1;
		}
		else
		{
			if (current_frame >= 0.0f)
				current_frame -= speed * servicesManager->time->frameTimeSeconds;

			if (current_frame >= 0)
				valid_frame = (int)current_frame;
			else
				valid_frame = 0;
		}
	}
}

bool Animation::HasFinished() const
{
	if (forward)
		return (!loop && current_frame >= framesSize);
	else
		return (!loop && current_frame < 0.0f);
}

const Sprite& Animation::GetFrame() const
{
	return frames[valid_frame];
}

void Animation::NextFrame()
{
	current_frame += 1.0f;
	if (current_frame >= framesSize)
		current_frame = 0.0f;
}

void Animation::PriorFrame()
{
	current_frame -= 1.0f;
	if (current_frame < 0.0f)
		current_frame = framesSize - 1.0f;
}
