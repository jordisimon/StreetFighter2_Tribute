#include "ModuleTextures.h"
#include "Defines.h"
#include "Game.h"
#include "ModuleRender.h"

using namespace std;

bool ModuleTextures::Init()
{
	LOG("Init Image library");

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

bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(*it);

	textures.clear();

	IMG_Quit();

	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
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
			textures.push_back(texture);
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

// Free texture from memory
void ModuleTextures::Unload(SDL_Texture* texture)
{
	for (list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if (*it == texture)
		{
			SDL_DestroyTexture(*it);
			textures.erase(it);
			break;
		}
	}
}
