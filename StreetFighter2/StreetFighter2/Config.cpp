#include "Config.h"
#include <cstdlib>
#include "Defines.h"
#include "AnimationColliderInfo.h"

Config::Config()
{
	auxKey = new char[100]; //should be enough for all keys in config file
	result = new char[100];
}

Config::~Config()
{
	RELEASE_ARRAY(result);
	RELEASE_ARRAY(auxKey);
}

bool Config::Init()
{
	LOG("Loading config --------------");
	ini.SetUnicode();
	
	return ini.LoadFile("config.ini") == SI_OK;
}

const char* Config::LoadCharValue(const char * sectionName, const char * keyName, const char* defaultValue) const
{
	return ini.GetValue(sectionName, keyName, defaultValue);
}

int Config::LoadIntValue(const char * sectionName, const char * keyName, const char* defaultValue) const
{
	return atoi(ini.GetValue(sectionName, keyName, defaultValue));
}

float Config::LoadFloatValue(const char * sectionName, const char * keyName, const char * defaultValue) const
{
	return (float)atof(ini.GetValue(sectionName, keyName, defaultValue));;
}

bool Config::LoadBoolValue(const char * sectionName, const char * keyName, const char * defaultValue) const
{
	return atoi(ini.GetValue(sectionName, keyName, defaultValue)) != 0;
}

bool Config::LoadiPoint(iPoint & point, const char * sectionName, const char * keyName) const
{
	strcpy(result, ini.GetValue(sectionName, keyName, "0,0"));

	point.x = atoi(strtok(result, ","));
	point.y = atoi(strtok(NULL, ","));

	return true;
}

bool Config::LoadfPoint(fPoint & point, const char * sectionName, const char * keyName) const
{
	strcpy(result, ini.GetValue(sectionName, keyName, "0.0f,0.0f"));

	point.x = (float)atof(strtok(result, ","));
	point.y = (float)atof(strtok(NULL, ","));

	return true;
}

bool Config::LoadiRect(iRect& rect, const char * sectionName, const char * keyName) const
{
	strcpy(result, ini.GetValue(sectionName, keyName, "0,0,0,0"));

	rect.x = atoi(strtok(result, ","));
	rect.y = atoi(strtok(NULL, ","));
	rect.w = atoi(strtok(NULL, ","));
	rect.h = atoi(strtok(NULL, ","));

	return true;
}

bool Config::LoadfRect(fRect& rect, const char * sectionName, const char * keyName) const
{
	strcpy(result, ini.GetValue(sectionName, keyName, "0,0,0,0"));

	rect.x = (float)atof(strtok(result, ","));
	rect.y = (float)atof(strtok(NULL, ","));
	rect.w = (float)atof(strtok(NULL, ","));
	rect.h = (float)atof(strtok(NULL, ","));

	return true;
}

bool Config::LoadSprite(Sprite& sprite, const char* sectionName, const char* keyName) const
{
	strcpy(result, ini.GetValue(sectionName, keyName, "0,0,0,0,0,0"));

	sprite.rect.x = (float)atof(strtok(result, ","));
	sprite.rect.y = (float)atof(strtok(NULL, ","));
	sprite.rect.w = (float)atof(strtok(NULL, ","));
	sprite.rect.h = (float)atof(strtok(NULL, ","));
	sprite.offset.x = (float)atof(strtok(NULL, ","));
	sprite.offset.y = (float)atof(strtok(NULL, ","));

	return true; //useless right now, but ready for some kind of error control in the future
}

bool Config::LoadAnimation(Animation & animation, const char * sectionName, const char * keyName) const
{
	int frameNum = 0;
	char* frameNumChar = new char[3];
	float frameX, frameY, frameW, frameH, frameOffsetX, frameOffsetY;

	bool frameFound;
	do
	{
		sprintf(frameNumChar, "%d", frameNum);

		strcpy(auxKey, keyName); strcat(auxKey, frameNumChar);
		strcpy(result, ini.GetValue(sectionName, auxKey, "-1,-1,-1,-1,-1,-1"));

		frameX = (float)atof(strtok(result, ","));
		frameY = (float)atof(strtok(NULL, ","));
		frameW = (float)atof(strtok(NULL, ","));
		frameH = (float)atof(strtok(NULL, ","));
		frameOffsetX = (float)atof(strtok(NULL, ","));
		frameOffsetY = (float)atof(strtok(NULL, ","));
		
		frameFound = (frameX != -1 && frameY != -1 && frameW != -1 && frameH != -1);

		if (frameFound)
		{
			animation.frames.push_back({ { frameX, frameY, frameW, frameH }, { frameOffsetX, frameOffsetY } });
		}

		++frameNum;
	} while (frameFound);

	animation.SetFramesSize();

	//strcpy(auxKey, keyName); strcat(auxKey, "Speed");
	//animation.SetSpeed((float)atof(ini.GetValue(sectionName, auxKey, "1.0f")));
	strcpy(auxKey, keyName); strcat(auxKey, "Duration");
	animation.SetDuration((float)atof(ini.GetValue(sectionName, auxKey, "1.0f")));

	strcpy(auxKey, keyName); strcat(auxKey, "Loop");
	animation.loop = atoi(ini.GetValue(sectionName, auxKey, "1")) != 0;

	RELEASE_ARRAY(frameNumChar);
	return true;
}

bool Config::LoadAnimationCollider(AnimationCollider& animation, const char* sectionName, const char * keyName) const
{
	LoadAnimation(animation, sectionName, keyName);

	int colliderNum = 0;
	char* colliderNumChar = new char[3];

	int colliderFrameNum = 0;
	char* colliderFrameNumChar = new char[3];

	bool colliderFound;
	bool colliderFrameFound;

	int colliderType;
	float frameX, frameY, frameW, frameH, frameOffsetX, frameOffsetY;
	bool active;

	do
	{
		//Search collider
		sprintf(colliderNumChar, "%d", colliderNum);
		strcpy(auxKey, keyName); strcat(auxKey, "Col"); strcat(auxKey, colliderNumChar); strcat(auxKey, "Type");

		colliderType = atoi(ini.GetValue(sectionName, auxKey, "-1"));

		colliderFound = colliderType > -1;

		if (colliderFound)
		{
			AnimationColliderInfo* animInfo = new AnimationColliderInfo();
			animInfo->type = (ColliderType)colliderType;

			colliderFrameNum = 0;
			do
			{
				//Search collider frames
				sprintf(colliderFrameNumChar, "%d", colliderFrameNum);
				strcpy(auxKey, keyName); strcat(auxKey, "Col"); strcat(auxKey, colliderNumChar); strcat(auxKey, colliderFrameNumChar);
				strcpy(result, ini.GetValue(sectionName, auxKey, "-1,-1,-1,-1,-1,-1,-1"));

				frameX = (float)atof(strtok(result, ","));
				frameY = (float)atof(strtok(NULL, ","));
				frameW = (float)atof(strtok(NULL, ","));
				frameH = (float)atof(strtok(NULL, ","));
				frameOffsetX = (float)atof(strtok(NULL, ","));
				frameOffsetY = (float)atof(strtok(NULL, ","));
				active = atoi(strtok(NULL, ",")) != 0;

				colliderFrameFound = (frameX != -1 && frameY != -1 && frameW != -1 && frameH != -1);

				if (colliderFrameFound)
				{
					animInfo->colliderFrameSprites.push_back({ { frameX, frameY, frameW, frameH }, { frameOffsetX, frameOffsetY } });
					animInfo->colliderFrameActive.push_back(active);
					animInfo->colliderCurrentFrameActive.push_back(active);

					++colliderFrameNum;
				}
			} while (colliderFrameFound);


			if (animInfo->colliderFrameSprites.size() == animation.frames.size())
			{
				animation.colliderAnimationList.push_back(animInfo);
			} 
			else
			{
				RELEASE(animInfo);
			}

			++colliderNum;
		}

	} while (colliderFound);

	RELEASE_ARRAY(colliderFrameNumChar);
	RELEASE_ARRAY(colliderNumChar);
	return true;
}


