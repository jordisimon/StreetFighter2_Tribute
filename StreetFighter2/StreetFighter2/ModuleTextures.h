#pragma once
#include "Module.h"
#include <list>
#include "SDL\include\SDL_image.h"

struct SDL_Texture;

class ModuleTextures :	public Module
{
private:
	std::list<SDL_Texture*> textures;

public:
	ModuleTextures() {};
	~ModuleTextures() {};

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);
};

