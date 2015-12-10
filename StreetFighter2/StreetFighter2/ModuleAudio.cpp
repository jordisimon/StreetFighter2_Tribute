#include "ModuleAudio.h"
#include "Defines.h"
#include "Config.h"

#include "SDL/include/SDL.h"
#include "SDL\include\SDL_mixer.h"

#define CONFIG_SECTION "Audio"

using namespace std;

bool ModuleAudio::Init(const Config& config)
{
	LOG("Loading Audio Mixer");

	fadeTime = config.LoadFloatValue(CONFIG_SECTION, "fadeTime", "2.0f");

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		return false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != nullptr)
	{
		Mix_FreeMusic(music);
	}

	for (vector<Mix_Chunk*>::iterator it = fx.begin(); it != fx.end(); ++it)
		Mix_FreeChunk(*it);

	fx.clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

bool ModuleAudio::PlayMusic(const char * path)
{
	return PlayMusic(path, fadeTime);
}

bool ModuleAudio::PlayMusic(const char * path, float pFade_time)
{
	bool ret = true;

	if (music != nullptr)
	{
		if (pFade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(pFade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == nullptr)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (pFade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(pFade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}
