#pragma once
#include "Module.h"
#include <vector>

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ModuleAudio :	public Module
{
private:
	float fadeTime;

	Mix_Music*	music = nullptr;
	std::vector<Mix_Chunk*>	fx;

public:
	ModuleAudio() {};
	~ModuleAudio() {};

	bool Init(const Config& config);
	bool CleanUp();

	bool PlayMusic(const char* path);
	bool PlayMusic(const char* path, float pFade_time);
};

