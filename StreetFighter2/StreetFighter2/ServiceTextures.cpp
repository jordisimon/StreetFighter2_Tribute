#include "ServiceTextures.h"
#include "Defines.h"
#include "Game.h"
#include "Config.h"
#include "ServiceRender.h"

using namespace std;

bool ServiceTextures::Init(const Config& config)
{
	LOG("Init Textures Service");

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		return false;
	}

	return true;
}

bool ServiceTextures::CleanUp()
{
	LOG("CleanUp Textures Service");

	for (map<int, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(it->second);

	textures.clear();

	IMG_Quit();

	return true;
}

SDL_Texture* const ServiceTextures::Load(const char * configSection)
{
	//Find texture id
	int textureId = game->config.LoadIntValue(configSection, "spriteSheetId", "-1");

	if (textureId == -1)
		return nullptr;

	//If texture already loaded, return it
	map<int, SDL_Texture*>::const_iterator tex = textures.find(textureId);
	if (tex != textures.cend())
	{
		return tex->second;
	}

	//Find texture path
	const char* path = game->config.LoadCharValue(configSection, "spriteSheetName", "");

	//Load texture and insert into map
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == nullptr)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(game->sRender->renderer, surface);

		if (texture == nullptr)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textures[textureId] = texture;
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

// Load new texture from file path
SDL_Texture* const ServiceTextures::Load(const char* path, int id)
{
	map<int, SDL_Texture*>::const_iterator tex = textures.find(id);
	if (tex != textures.cend())
	{
		return tex->second;
	}

	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == nullptr)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(game->sRender->renderer, surface);

		if (texture == nullptr)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textures[id] = texture;
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

// Free texture from memory
void ServiceTextures::Unload(const SDL_Texture* texture)
{
	for (map<int, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if (it->second == texture)
		{
			SDL_DestroyTexture(it->second);
			textures.erase(it);
			break;
		}
	}
}

void ServiceTextures::Unload(int id)
{
	map<int, SDL_Texture*>::const_iterator tex = textures.find(id);
	if (tex != textures.cend())
	{
		SDL_DestroyTexture(tex->second);
		textures.erase(tex);
	}
}

