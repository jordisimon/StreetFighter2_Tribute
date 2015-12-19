#include "Config.h"
#include <cstdlib>
#include "Defines.h"

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

bool Config::LoadPoint(iPoint & point, const char * sectionName, const char * keyName) const
{
	strcpy(result, ini.GetValue(sectionName, keyName, "0,0"));

	point.x = atoi(strtok(result, ","));
	point.y = atoi(strtok(NULL, ","));

	return true;
}

bool Config::LoadSDLRect(SDL_Rect & rect, const char * sectionName, const char * keyName) const
{
	strcpy(result, ini.GetValue(sectionName, keyName, "0,0,0,0"));

	rect.x = atoi(strtok(result, ","));
	rect.y = atoi(strtok(NULL, ","));
	rect.w = atoi(strtok(NULL, ","));
	rect.h = atoi(strtok(NULL, ","));

	return true;
}

bool Config::LoadSprite(Sprite& sprite, const char* sectionName, const char* keyName) const
{
	strcpy(result, ini.GetValue(sectionName, keyName, "0,0,0,0,0,0"));

	sprite.rect.x = atoi(strtok(result, ","));
	sprite.rect.y = atoi(strtok(NULL, ","));
	sprite.rect.w = atoi(strtok(NULL, ","));
	sprite.rect.h = atoi(strtok(NULL, ","));
	sprite.offset.x = atoi(strtok(NULL, ","));
	sprite.offset.y = atoi(strtok(NULL, ","));

	return true; //useless right now, but ready for some kind of error control in the future
}

bool Config::LoadAnimation(Animation & animation, const char * sectionName, const char * keyName) const
{
	int frameNum = 0;
	char* frameNumChar = new char[3];
	int frameX, frameY, frameW, frameH, frameOffsetX, frameOffsetY;

	bool frameFound;
	do
	{
		sprintf(frameNumChar, "%d", frameNum);

		strcpy(auxKey, keyName); strcat(auxKey, frameNumChar);
		strcpy(result, ini.GetValue(sectionName, auxKey, "-1,-1,-1,-1,-1,-1"));

		frameX = atoi(strtok(result, ","));
		frameY = atoi(strtok(NULL, ","));
		frameW = atoi(strtok(NULL, ","));
		frameH = atoi(strtok(NULL, ","));
		frameOffsetX = atoi(strtok(NULL, ","));
		frameOffsetY = atoi(strtok(NULL, ","));
		
		frameFound = (frameX != -1 && frameY != -1 && frameW != -1 && frameH != -1);

		if (frameFound)
		{
			animation.frames.push_back({ { frameX, frameY, frameW, frameH },{ frameOffsetX, frameOffsetY } });
		}

		frameNum++;
	} while (frameFound);


	strcpy(auxKey, keyName); strcat(auxKey, "Speed");

	animation.speed = (float)atof(ini.GetValue(sectionName, auxKey, "1.0f"));

	RELEASE_ARRAY(frameNumChar);
	return true;
}


