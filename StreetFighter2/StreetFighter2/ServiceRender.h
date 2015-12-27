#pragma once
#include "Service.h"
#include "Point.h"
#include "Rect.h"
#include "Color.h"
#include "Direction.h"

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
	int screenHRatio;
	int screenVRatio;
	bool fullScreen;
	bool vSync;

	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;
	fRect camera;
	fRect cameraRender;
	fPoint screenCenter;

	bool Blit(SDL_Texture* texture, const fPoint& position, const fRect& section, bool gui, float speed = 1.0f, Direction direction = Direction::RIGHT, float scale = 1.0f);
	void DrawRect(const fRect& rect, bool gui, bool fill);

public:
	SDL_Renderer* renderer = nullptr;

	ServiceRender() {};
	~ServiceRender() {};

	bool Init();
	bool CleanUp();

	bool BlitScene(SDL_Texture* texture, const fPoint& position, const fRect& section, float speed = 1.0f, Direction direction = Direction::RIGHT, float scale = 1.0f);
	bool BlitGUI(SDL_Texture* texture, const fPoint& position, const fRect& section, Direction direction = Direction::RIGHT, float scale = 1.0f);

	void SetDrawColor(const Color& color) const;
	void DrawRectLine(const fRect& rect, bool gui = false);
	void DrawRectFill(const fRect& rect, bool gui = false);

	void SetCameraPostion(const fPoint& position);
	void MoveCamera(const fPoint& offset);
	const fRect& GetCamera() const;
	const fPoint& GetScreenCenter() const;

	bool ClearRender() const;
	bool PresentRender() const;
};

