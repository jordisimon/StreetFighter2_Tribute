#pragma once
#include "Module.h"
#include "Point.h"

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

class ModuleInput :	public Module
{
private:
	bool		windowEvents[(int)EventWindow::WE_COUNT];
	KeyState	keyboard[MAX_KEYBOARD_KEYS];
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	iPoint mouse_motion;
	iPoint mouse;
	int screenSize;

public:
	ModuleInput();
	~ModuleInput() {};

	bool Init(const Config& config);
	bool CleanUp();

	Module::Update_result PreUpdate();

	KeyState GetKey(int id) const
	{
		return keyboard[id];
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

