#include "Animation.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTime.h"

Animation::Animation() : frames{}, currentSpeed{ 1.0f }, currentFrame{ 0.0f }, validFrame{ 0 }, loop{ true }, forward{ true }, loopsCompleted{ 0 }, speedAltered{ false }, originalSpeed{ 1.0f }, timer{ 100 }
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
	originalSpeed = sp * frames.size();
	ResetOriginalSpeed();
}

void Animation::SetDuration(float dur)
{
	originalSpeed = (1 / dur) * frames.size();
	ResetOriginalSpeed();
}

void Animation::ResetOriginalSpeed()
{
	currentSpeed = originalSpeed;
	timer.Reset();
	timer.Pause();
	speedAltered = false;
}

void Animation::ResetAnimation()
{ 
	loopsCompleted = 0;
	if (forward)
		currentFrame = 0.0f;
	else
		currentFrame = (float)framesSize - 1;

	validFrame = (int)currentFrame;

	ResetOriginalSpeed();

	OnRestart();
}

void Animation::UpdateCurrentFrame()
{
	//Return to original speed
	if (speedAltered && timer.Reached())
	{
		ResetOriginalSpeed();
	}

	if (loop)
	{
		if (forward)
		{
			currentFrame += currentSpeed * servicesManager->time->frameTimeSeconds;
			if (currentFrame >= framesSize)
			{
				++loopsCompleted;
				currentFrame = 0.0f;
				OnRestart();
			}
		}
		else
		{
			currentFrame -= currentSpeed * servicesManager->time->frameTimeSeconds;
			if (currentFrame < 0.0f)
			{
				++loopsCompleted;
				currentFrame = (float)framesSize - 1;
				OnRestart();
			}
		}
		validFrame = (int)currentFrame;
	}
	else
	{
		if (forward)
		{
			if (currentFrame <= framesSize)
				currentFrame += currentSpeed * servicesManager->time->frameTimeSeconds;

			if (currentFrame < framesSize)
				validFrame = (int)currentFrame;
			else
				validFrame = framesSize - 1;
		}
		else
		{
			if (currentFrame >= 0.0f)
				currentFrame -= currentSpeed * servicesManager->time->frameTimeSeconds;

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
	currentSpeed *= ratio;
	timer.Resume();
	timer.SetNewInterval(time);
	speedAltered = true;
}
