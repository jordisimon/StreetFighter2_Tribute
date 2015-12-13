#pragma once
#include "SimpleIni.h"
#include "Sprite.h"
#include "Animation.h"

class Config
{
private:
	char* auxKey;
	char* result;
	CSimpleIniA ini;

public:
	Config();

	~Config();

	bool Init();

	const char* LoadCharValue(const char * sectionName, const char * keyName, const char* defaultValue) const;
	int LoadIntValue(const char* sectionName, const char* keyName, const char* defaultValue) const;
	float LoadFloatValue(const char* sectionName, const char* keyName, const char* defaultValue) const;
	bool LoadBoolValue(const char* sectionName, const char* keyName, const char* defaultValue) const;

	bool LoadSprite(Sprite& sprite, const char* sectionName, const char* keyName) const;
	bool LoadPoint(iPoint& point, const char * sectionName, const char * keyName) const;
	bool LoadAnimation(Animation& animation, const char* sectionName, const char* keyName) const;
};

