#pragma once
#include "SimpleIni.h"
#include "Sprite.h"
#include "Animation.h"

class Config
{
private:
	char* auxKey;
	CSimpleIniA ini;

public:
	Config();

	~Config();

	bool Init();

	int LoadIntValue(const char* sectionName, const char* keyName, const char* defaultValue) const;
	float LoadFloatValue(const char* sectionName, const char* keyName, const char* defaultValue) const;
	bool LoadBoolValue(const char* sectionName, const char* keyName, const char* defaultValue) const;

	bool LoadSprite(Sprite& sprite, const char* sectionName, const char* keyName) const;
	bool LoadPosition(iPoint& point, const char * sectionName, const char * keyName) const;
	bool LoadAnimation(Animation& animation, const char* sectionName, const char* keyName) const;
};

