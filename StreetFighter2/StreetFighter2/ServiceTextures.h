#pragma once
#include "Service.h"
#include <map>
#include "SDL\include\SDL_image.h"

struct SDL_Texture;

class ServiceTextures :	public Service
{
private:
	std::map<int, SDL_Texture*> textures;

public:
	ServiceTextures() {};
	~ServiceTextures() {};

	bool Init();
	bool CleanUp();

	SDL_Texture* Load(const char* configSection);
	SDL_Texture* Load(const char* path, int id);
	void Unload(const SDL_Texture* texture);
	void Unload(int id);
};

