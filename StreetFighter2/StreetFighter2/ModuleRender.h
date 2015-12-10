#pragma once
#include "Module.h"
#include "Point.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class ModuleRender : public Module
{
private:
	int screenWidth;
	int screenHeight;
	int screenRatio;
	bool fullScreen;
	bool vSync;

	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;
	SDL_Rect camera;

public:

	SDL_Renderer* renderer = nullptr;
	

	ModuleRender() {};
	~ModuleRender() {};

	bool Init(const Config& config);
	bool CleanUp();

	Update_result PreUpdate();
	Update_result Update();
	Update_result PostUpdate();

	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed = 1.0f);

	void MoveCamera(iPoint offset);
};

