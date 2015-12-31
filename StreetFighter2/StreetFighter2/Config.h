#pragma once
#include "SimpleIni.h"
#include "Point.h"
#include "Rect.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationCollider.h"

class Config
{
private:
	char* auxKey = nullptr;
	char* result = nullptr;
	CSimpleIniA ini;

public:
	Config();

	~Config();

	bool Init();

	const char* LoadCharValue(const char * sectionName, const char * keyName, const char* defaultValue) const;
	int LoadIntValue(const char* sectionName, const char* keyName, const char* defaultValue) const;
	float LoadFloatValue(const char* sectionName, const char* keyName, const char* defaultValue) const;
	bool LoadBoolValue(const char* sectionName, const char* keyName, const char* defaultValue) const;

	bool LoadiPoint(iPoint& point, const char * sectionName, const char * keyName) const;
	bool LoadfPoint(fPoint& point, const char * sectionName, const char * keyName) const;
	bool LoadiRect(iRect& rect, const char * sectionName, const char * keyName) const;
	bool LoadfRect(fRect& rect, const char * sectionName, const char * keyName) const;

	bool LoadSprite(Sprite& sprite, const char* sectionName, const char* keyName) const;
	bool LoadAnimation(Animation& animation, const char* sectionName, const char* keyName) const;
	bool LoadAnimationCollider(AnimationCollider& animation, const char* sectionName, const char* keyName) const;
};

extern Config* config;

