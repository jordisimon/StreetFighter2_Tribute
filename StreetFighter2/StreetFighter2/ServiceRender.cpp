#include "ServiceRender.h"
#include "Defines.h"
#include "Config.h"
#include "SDL\include\SDL.h"

#define CONFIG_SECTION "Render"

bool ServiceRender::Init()
{
	LOG("Init Render Service");

	screenWidth = config->LoadIntValue(CONFIG_SECTION, "screenWidth", "384");
	screenHeight = config->LoadIntValue(CONFIG_SECTION, "screenHeight", "224");
	screenRatio = config->LoadIntValue(CONFIG_SECTION, "screenRatio", "2");
	fullScreen = config->LoadBoolValue(CONFIG_SECTION, "fullScreen", "0");
	vSync = config->LoadBoolValue(CONFIG_SECTION, "vSync", "384");

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

bool ServiceRender::CleanUp()
{
	LOG("CleanUp Render Service");

	LOG("Destroying renderer");

	//Destroy window
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	LOG("Destroying SDL window and quitting video subsystem");

	//Destroy window
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	return true;
}

bool ServiceRender::Blit(SDL_Texture* texture,const iPoint& position, const SDL_Rect* section, float speed, Direction direction) const
{
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + position.x * screenRatio;
	//rect.y = (int)(camera.y * speed) + y * screenSize;
	rect.y = (camera.y) + position.y * screenRatio; //No vertical parallax

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

	SDL_RendererFlip flip;
	if (direction == Direction::RIGHT)
		flip = SDL_FLIP_NONE;
	else
		flip = SDL_FLIP_HORIZONTAL;

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, 0.0, NULL, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		return false;
	}

	return true;
}

void ServiceRender::SetDrawColor(const Color& color) const
{
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
}

void ServiceRender::DrawRect(const SDL_Rect* rect) const
{
	SDL_Rect rectAux;
	rectAux.x = (int)(camera.x) + rect->x * screenRatio;
	//rect.y = (int)(camera.y * speed) + y * screenSize;
	rectAux.y = (camera.y) + rect->y * screenRatio; //No vertical parallax

	rectAux.w = rect->w * screenRatio;
	rectAux.h = rect->h * screenRatio;

	SDL_RenderDrawRect(renderer, &rectAux);
}

bool ServiceRender::HasIntersection(const SDL_Rect* rectA, const SDL_Rect* rectB)
{
	return SDL_HasIntersection(rectA, rectB) == SDL_TRUE;
}

void ServiceRender::SetCameraPostion(const iPoint& position)
{
	camera.x = position.x;
	camera.y = position.y;
}

void ServiceRender::MoveCamera(const iPoint& offset)
{
	camera.x += offset.x;
	camera.y += offset.y;
}

bool ServiceRender::ClearRender() const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return true;
}

bool ServiceRender::PresentRender() const
{
	SDL_RenderPresent(renderer);
	return true;
}
