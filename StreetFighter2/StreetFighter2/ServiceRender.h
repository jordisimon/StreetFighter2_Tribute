#pragma once
#include "Service.h"
#include "Point.h"
#include "Color.h"
#include "Direction.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class ServiceRender : public Service
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

	ServiceRender() {};
	~ServiceRender() {};

	bool Init();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, const iPoint& position, const SDL_Rect* section, float speed = 1.0f, Direction direction = Direction::RIGHT) const;
	void SetDrawColor(const Color& color) const;
	void DrawRect(const SDL_Rect* rect) const;
	bool HasIntersection(const SDL_Rect* rectA, const SDL_Rect* rectB);
	void SetCameraPostion(const iPoint& position);
	void MoveCamera(const iPoint& offset);

	bool ClearRender() const;
	bool PresentRender() const;
};

