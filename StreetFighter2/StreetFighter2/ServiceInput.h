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

enum class GameControllerButton
{
    CONTROLLER_BUTTON_INVALID = -1,
    CONTROLLER_BUTTON_A,
    CONTROLLER_BUTTON_B,
    CONTROLLER_BUTTON_X,
    CONTROLLER_BUTTON_Y,
    CONTROLLER_BUTTON_BACK,
    CONTROLLER_BUTTON_GUIDE,
    CONTROLLER_BUTTON_START,
    CONTROLLER_BUTTON_LEFTSTICK,
    CONTROLLER_BUTTON_RIGHTSTICK,
    CONTROLLER_BUTTON_LEFTSHOULDER,
	CONTROLLER_BUTTON_RIGHTSHOULDER,
    CONTROLLER_BUTTON_DPAD_UP,
    CONTROLLER_BUTTON_DPAD_DOWN,
    CONTROLLER_BUTTON_DPAD_LEFT,
    CONTROLLER_BUTTON_DPAD_RIGHT,
	//Added diagonals
	CONTROLLER_BUTTON_DPAD_UP_LEFT,
	CONTROLLER_BUTTON_DPAD_UP_RIGHT,
	CONTROLLER_BUTTON_DPAD_DOWN_LEFT,
	CONTROLLER_BUTTON_DPAD_DOWN_RIGHT,
    CONTROLLER_BUTTON_MAX
};

class ServiceInput : public Service
{
private:
	bool		windowEvents[(int)EventWindow::WE_COUNT];
	KeyState	keyboard[MAX_KEYBOARD_KEYS];
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	KeyState	gameController1[(int)GameControllerButton::CONTROLLER_BUTTON_MAX];
	KeyState	gameController2[(int)GameControllerButton::CONTROLLER_BUTTON_MAX];
	iPoint mouse_motion;
	iPoint mouse;
	SDL_GameController* controller1 = nullptr;
	SDL_GameController* controller2 = nullptr;
	SDL_Haptic* haptic1 = nullptr;
	SDL_Haptic* haptic2 = nullptr;
	float axisThreshold;
	int screenSize;
	bool controllerOverridesKeyboard;

	void UpdateGameControllerState(SDL_GameController* controller, KeyState* controllerState);

public:
	ServiceInput();
	~ServiceInput() {};

	bool Init();
	bool CleanUp();

	bool UpdateInput();

	bool GetControllerOverridesKeyboard() const { return controllerOverridesKeyboard; }

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