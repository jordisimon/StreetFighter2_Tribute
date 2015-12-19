#pragma once
#include "Service.h"
#include "Point.h"
#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL_haptic.h"

#define NUM_MOUSE_BUTTONS 5
#define MAX_KEYBOARD_KEYS 300

enum class EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum class KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ServiceInput : public Service
{
private:
	bool		windowEvents[(int)EventWindow::WE_COUNT];
	KeyState	keyboard[MAX_KEYBOARD_KEYS];
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	KeyState	gameController1[SDL_CONTROLLER_BUTTON_MAX];
	KeyState	gameController2[SDL_CONTROLLER_BUTTON_MAX];
	iPoint mouse_motion;
	iPoint mouse;
	SDL_GameController* controller1 = nullptr;
	SDL_GameController* controller2 = nullptr;
	SDL_Haptic* haptic1 = nullptr;
	SDL_Haptic* haptic2 = nullptr;
	int screenSize;

	void UpdateGameControllerState(SDL_GameController* controller, KeyState* controllerState);

public:
	ServiceInput();
	~ServiceInput() {};

	bool Init();
	bool CleanUp();

	bool UpdateInput();

	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	bool ExistController(int controllerNumber) const
	{
		switch (controllerNumber)
		{
		case 1:
			return controller1 != nullptr;
			break;
		case 2:
			return controller2 != nullptr;
			break;
		}
		return false;
	}

	KeyState GetControllerButton(int controller, int button) const
	{
		switch (controller)
		{
		case 1:
			return gameController1[button];
			break;
		case 2:
			return gameController2[button];
			break;
		}

		return KeyState::KEY_IDLE;
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	// Check for window events last frame
	bool GetWindowEvent(EventWindow ev) const
	{
		return windowEvents[(int)ev];
	}
};