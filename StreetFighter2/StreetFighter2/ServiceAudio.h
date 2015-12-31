#pragma once
#include "Service.h"
#include <vector>

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ServiceAudio : public Service
{
private:
	float fadeTime;

	Mix_Music*	music = nullptr;
	std::vector<Mix_Chunk*>	fx;

public:
	ServiceAudio() {};
	~ServiceAudio() {};

	bool Init();
	bool CleanUp();

	bool PlayMusic(const char* path);
	bool PlayMusic(const char* path, float pFade_time);
	bool PauseMusic() const;
	bool ResumeMusic() const;
	bool StopMusic() const;
	bool StopMusic(float pFade_time) const;

	int LoadFx(const char* path);
	bool PlayFx(unsigned int fx, int repeat = 0) const;
};

