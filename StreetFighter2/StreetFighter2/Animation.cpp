#include "Animation.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTime.h"

Animation::Animation() : frames{}, speed{ 1.0f }, currentFrame{ 0.0f }, loop{ true }, forward{ true }, loopsCompleted{ 0 }, speedAltered{ false }, originalSpeed{ 1.0f }, timer{100}
{
}

Animation::~Animation()
{
}

void Animation::SetFramesSize()
{
	framesSize = (int)frames.size();
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
	loopsCompleted = 0;
	if (forward)
		currentFrame = 0.0f;
	else
		currentFrame = (float)framesSize - 1;

	validFrame = (int)currentFrame;

	OnReset();
}

void Animation::UpdateCurrentFrame()
{
	//Return to original speed
	if (speedAltered && timer.Reached())
	{
		speedAltered = false;
		speed = originalSpeed;
	}

	if (loop)
	{
		if (forward)
		{
			currentFrame += speed * servicesManager->time->frameTimeSeconds;
			if (currentFrame >= framesSize)
			{
				++loopsCompleted;
				currentFrame = 0.0f;
				OnReset();
			}
		}
		else
		{
			currentFrame -= speed * servicesManager->time->frameTimeSeconds;
			if (currentFrame < 0.0f)
			{
				++loopsCompleted;
				currentFrame = (float)framesSize - 1;
				OnReset();
			}
		}
		validFrame = (int)currentFrame;
	}
	else
	{
		if (forward)
		{
			if (currentFrame <= framesSize)
				currentFrame += speed * servicesManager->time->frameTimeSeconds;

			if (currentFrame < framesSize)
				validFrame = (int)currentFrame;
			else
				validFrame = framesSize - 1;
		}
		else
		{
			if (currentFrame >= 0.0f)
				currentFrame -= speed * servicesManager->time->frameTimeSeconds;

			if (currentFrame >= 0)
				validFrame = (int)currentFrame;
			else
				validFrame = 0;
		}
	}
}

bool Animation::HasFinished() const
{
	if (forward)
		return (!loop && currentFrame >= framesSize);
	else
		return (!loop && currentFrame < 0.0f);
}

const Sprite& Animation::GetFrame() const
{
	return frames[validFrame];
}

int Animation::GetCurrentFrameIndex() const
{
	return validFrame;
}

void Animation::ChangeSpeedTemporal(float ratio, int time)
{
	originalSpeed = speed;
	speed *= ratio;
	timer.SetNewInterval(time);
	speedAltered = true;
}
