#pragma once
#include "Module.h"

struct SDL_Texture;

class Stage : public Module
{
public:
	SDL_Texture* graphics = nullptr;
	const char* spriteSheetName;
	const char* musicName;

	int camMinX;
	int camMinY;
	int camMaxX;
	int camMaxY;
	int groundLevel;

	Stage() {};
	~Stage() {};

	bool Start();
	bool Stop();
};

