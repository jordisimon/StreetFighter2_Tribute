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

	bool Init(const Config& config);
	bool CleanUp();

	SDL_Texture* const Load(const char* configSection);
	SDL_Texture* const Load(const char* path, int id);
	void Unload(const SDL_Texture* texture);
	void Unload(int id);
};

