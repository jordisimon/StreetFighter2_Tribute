#include "ServiceRender.h"
#include "Defines.h"
#include "Config.h"
#include <math.h>
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_rect.h"
#include "SDL\include\SDL_pixels.h"

#define CONFIG_SECTION "Render"

bool ServiceRender::Init()
{
	LOG("Init Render Service");

	screenWidth = config->LoadIntValue(CONFIG_SECTION, "screenWidth", "384");
	screenHeight = config->LoadIntValue(CONFIG_SECTION, "screenHeight", "224");
	screenRatio = config->LoadIntValue(CONFIG_SECTION, "screenRatio", "2");
	screenHRatio = config->LoadIntValue(CONFIG_SECTION, "screenHRatio", "2");
	screenVRatio = config->LoadIntValue(CONFIG_SECTION, "screenVRatio", "2");
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
	//int width = screenWidth * screenRatio;
	//int height = screenHeight * screenRatio;
	int width = screenWidth * screenHRatio;
	int height = screenHeight * screenVRatio;
	screenCenter.x = (float)screenWidth / 2;
	screenCenter.y = (float)screenHeight / 2;

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
	camera.x = camera.y = 0.0f;
	camera.w = (float)screenWidth;
	camera.h = (float)screenHeight;
	cameraRender.x = cameraRender.y = 0.0f;
	cameraRender.w = (float)width;
	cameraRender.y = (float)height;

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

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	return true;
}

bool ServiceRender::CleanUp()
{
	LOG("CleanUp Render Service");

	LOG("Destroying renderer\n");

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


bool ServiceRender::Blit(SDL_Texture* texture, const fPoint& position, const fRect& section, bool gui, float speed, Direction direction, float scale) const
{
	SDL_Rect source {(int)section.x, (int)section.y, (int)section.w, (int)section.h};
	SDL_Rect dest;

	//GUI
	if (gui)
	{
		dest.x = (int)(position.x * screenHRatio);
		dest.y = (int)(position.y * screenVRatio);
	}
	//Scene
	else
	{
		dest.x = (int)floor((cameraRender.x * speed) + position.x * screenHRatio);
		dest.y = (int)floor((cameraRender.y) + position.y * screenVRatio); //No vertical parallax
	}

	dest.w = (int)(section.w * screenHRatio * scale);
	dest.h = (int)(section.h * screenVRatio * scale);


	SDL_RendererFlip flip;
	if (direction == Direction::RIGHT)
		flip = SDL_FLIP_NONE;
	else
		flip = SDL_FLIP_HORIZONTAL;

	if (SDL_RenderCopyEx(renderer, texture, &source, &dest, 0.0, NULL, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		return false;
	}

	return true;
}

bool ServiceRender::BlitScene(SDL_Texture * texture, const fPoint & position, const fRect & section, float speed, Direction direction, float scale) const
{
	return Blit(texture, position, section, false, speed, direction, scale);
}

bool ServiceRender::BlitGUI(SDL_Texture * texture, const fPoint & position, const fRect & section, Direction direction, float scale) const
{
	return Blit(texture, position, section, true, 1.0f, direction, scale);
}


void ServiceRender::SetDrawColor(const Color& color) const
{
	if(SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha) != 0)
		LOG("Can not set draw color! SDL_Error: %s\n", SDL_GetError());
}

void ServiceRender::DrawRect(const fRect & rect, bool gui, bool fill) const
{
	SDL_Rect rectAux;

	//Gui
	if (gui)
	{
		rectAux.x = (int)rect.x * screenHRatio;
		rectAux.y = (int)rect.y * screenVRatio;
	}
	//Scene
	else
	{
		rectAux.x = (int)floor(cameraRender.x + rect.x * screenHRatio);
		rectAux.y = (int)floor(cameraRender.y + rect.y * screenVRatio); //No vertical parallax
	}

	rectAux.w = (int)rect.w * screenHRatio;
	rectAux.h = (int)rect.h * screenVRatio;

	if (fill)
	{
		if (SDL_RenderFillRect(renderer, &rectAux) != 0)
			LOG("Can not draw fill rect! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		if (SDL_RenderDrawRect(renderer, &rectAux) != 0)
			LOG("Can not draw rect! SDL_Error: %s\n", SDL_GetError());
	}
}

void ServiceRender::DrawRectLine(const fRect & rect, bool gui) const
{
	DrawRect(rect, gui, false);
}

void ServiceRender::DrawRectFill(const fRect & rect, bool gui) const
{
	DrawRect(rect, gui, true);
}

void ServiceRender::FillScreen() const
{
	SDL_RenderFillRect(renderer, NULL);
}


void ServiceRender::SetCameraPostion(const fPoint& position)
{
	camera.x = position.x;
	camera.y = position.y;
	cameraRender.x = camera.x * screenHRatio * -1;
	cameraRender.y = camera.y * screenVRatio * -1;
}

void ServiceRender::MoveCamera(const fPoint& offset)
{
	camera.x += offset.x;
	camera.y += offset.y;
	cameraRender.x = camera.x * screenHRatio * -1;
	cameraRender.y = camera.y * screenVRatio * -1;
}

const fRect& ServiceRender::GetCamera() const
{
	return camera;
}

const fPoint& ServiceRender::GetScreenCenter() const
{
	return screenCenter;
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
