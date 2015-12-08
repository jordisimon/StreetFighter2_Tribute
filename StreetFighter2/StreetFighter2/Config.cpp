#include "Config.h"
#include <cstdlib>
#include "Defines.h"

Config::Config()
{
	auxKey = new char[100]; //should be enough for all keys in config file
}

Config::~Config()
{
	RELEASE_ARRAY(auxKey);
}

bool Config::Init()
{
	LOG("Loading config --------------");
	ini.SetUnicode();
	
	return ini.LoadFile("config.ini") == SI_OK;
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

bool Config::LoadSprite(Sprite& sprite, const char* sectionName, const char* keyName) const
{
	strcpy(auxKey, keyName); strcat(auxKey, "X");
	sprite.rect.x = atoi(ini.GetValue(sectionName, auxKey, "0"));

	strcpy(auxKey, keyName); strcat(auxKey, "Y");
	sprite.rect.y = atoi(ini.GetValue(sectionName, auxKey, "0"));

	strcpy(auxKey, keyName); strcat(auxKey, "W");
	sprite.rect.w = atoi(ini.GetValue(sectionName, auxKey, "0"));

	strcpy(auxKey, keyName); strcat(auxKey, "H");
	sprite.rect.h = atoi(ini.GetValue(sectionName, auxKey, "0"));

	strcpy(auxKey, keyName); strcat(auxKey, "OffsetX");
	sprite.offset.x = atoi(ini.GetValue(sectionName, auxKey, "0"));

	strcpy(auxKey, keyName); strcat(auxKey, "OffsetY");
	sprite.offset.y = atoi(ini.GetValue(sectionName, auxKey, "0"));

	return true; //useless right now, but ready for some kind of error control in the future
}

bool Config::LoadPosition(iPoint & point, const char * sectionName, const char * keyName) const
{
	strcpy(auxKey, keyName); strcat(auxKey, "PosX");
	point.x = atoi(ini.GetValue(sectionName, auxKey, "0"));

	strcpy(auxKey, keyName); strcat(auxKey, "PosY");
	point.y = atoi(ini.GetValue(sectionName, auxKey, "0"));

	return true;
}

bool Config::LoadAnimation(Animation & animation, const char * sectionName, const char * keyName) const
{
	int frameNum = 0;
	char* frameNumChar = new char[3];
	int frameX, frameY, frameW, frameH, frameOffsetX, frameOffsetY;

	bool result;
	do
	{
		sprintf(frameNumChar, "%d", frameNum);

		strcpy(auxKey, keyName); strcat(auxKey, frameNumChar); strcat(auxKey, "X");
		frameX = atoi(ini.GetValue(sectionName, auxKey, "-1"));

		strcpy(auxKey, keyName); strcat(auxKey, frameNumChar); strcat(auxKey, "Y");
		frameY = atoi(ini.GetValue(sectionName, auxKey, "-1"));

		strcpy(auxKey, keyName); strcat(auxKey, frameNumChar); strcat(auxKey, "W");
		frameW = atoi(ini.GetValue(sectionName, auxKey, "-1"));

		strcpy(auxKey, keyName); strcat(auxKey, frameNumChar); strcat(auxKey, "H");
		frameH = atoi(ini.GetValue(sectionName, auxKey, "-1"));

		strcpy(auxKey, keyName); strcat(auxKey, frameNumChar); strcat(auxKey, "OffsetX");
		frameOffsetX = atoi(ini.GetValue(sectionName, auxKey, "0"));

		strcpy(auxKey, keyName); strcat(auxKey, frameNumChar); strcat(auxKey, "OffsetY");
		frameOffsetY = atoi(ini.GetValue(sectionName, auxKey, "0"));

		result = (frameX != -1 && frameY != -1 && frameW != -1 && frameH != -1);

		if (result)
			animation.frames.push_back({ { frameX, frameY, frameW, frameH }, { frameOffsetX, frameOffsetY } });

		frameNum++;
	} while (result);


	strcpy(auxKey, keyName); strcat(auxKey, "Speed");

	animation.speed = (float)atof(ini.GetValue(sectionName, auxKey, "1.0f"));

	RELEASE_ARRAY(frameNumChar);
	return true;
}


