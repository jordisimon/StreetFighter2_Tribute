#include "ModuleRender.h"
#include "Defines.h"
#include "Config.h"
#include "SDL\include\SDL.h"

#define CONFIG_SECTION "Render"

bool ModuleRender::Init(const Config& config)
{
	screenWidth = config.LoadIntValue(CONFIG_SECTION, "screenWidth", "384");
	screenHeight = config.LoadIntValue(CONFIG_SECTION, "screenHeight", "224");
	screenRatio = config.LoadIntValue(CONFIG_SECTION, "screenRatio", "2");
	fullScreen = config.LoadBoolValue(CONFIG_SECTION, "fullScreen", "0");
	vSync = config.LoadBoolValue(CONFIG_SECTION, "vSync", "384");

	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	int width = screenWidth * screenRatio;
	int height = screenHeight * screenRatio;
	Uint32 flags = SDL_WINDOW_SHOWN;

	if (fullScreen == true)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow("Street Fighter II", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

	if (window == nullptr)
	{
		LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Get window surface
	screen_surface = SDL_GetWindowSurface(window);

	//Camera settings
	camera.x = camera.y = 0;
	camera.w = width;
	camera.h = height;

	LOG("Creating Renderer context");
	flags = 0;

	if (vSync == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	return true;
}

Module::Update_result ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return Update_result::UPDATE_OK;
}

Module::Update_result ModuleRender::Update()
{
	return Update_result::UPDATE_OK;
}

Module::Update_result ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return Update_result::UPDATE_OK;
}

bool ModuleRender::Blit(SDL_Texture * texture, int x, int y, const SDL_Rect * section, float speed)
{
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * screenRatio;
	//rect.y = (int)(camera.y * speed) + y * screenSize;
	rect.y = (camera.y) + y * screenRatio; //No vertical parallax

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= screenRatio;
	rect.h *= screenRatio;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		return false;
	}

	return true;
}

void ModuleRender::MoveCamera(iPoint offset)
{
	camera.x += offset.x;
	camera.y += offset.y;
}
