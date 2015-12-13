#include "ServiceInput.h"
#include "Defines.h"
#include "Config.h"
#include "SDL\include\SDL.h"


ServiceInput::ServiceInput()
{
	memset(keyboard, (int)KeyState::KEY_IDLE, sizeof(KeyState) * MAX_KEYBOARD_KEYS);
	memset(mouse_buttons, (int)KeyState::KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

bool ServiceInput::Init(const Config & config)
{
	LOG("Init Input Service");

	screenSize = config.LoadIntValue("Render", "screenRatio", "2");

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

bool ServiceInput::CleanUp()
{
	LOG("CleanUp Input Service");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

bool ServiceInput::UpdateInput()
{
	static SDL_Event event;

	mouse_motion = { 0, 0 };
	memset(windowEvents, false, (int)EventWindow::WE_COUNT * sizeof(bool));

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KeyState::KEY_IDLE)
				keyboard[i] = KeyState::KEY_DOWN;
			else
				keyboard[i] = KeyState::KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KeyState::KEY_REPEAT || keyboard[i] == KeyState::KEY_DOWN)
				keyboard[i] = KeyState::KEY_UP;
			else
				keyboard[i] = KeyState::KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KeyState::KEY_DOWN)
			mouse_buttons[i] = KeyState::KEY_REPEAT;

		if (mouse_buttons[i] == KeyState::KEY_UP)
			mouse_buttons[i] = KeyState::KEY_IDLE;
	}

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			windowEvents[(int)EventWindow::WE_QUIT] = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
				//case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				windowEvents[(int)EventWindow::WE_HIDE] = true;
				break;

				//case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				windowEvents[(int)EventWindow::WE_SHOW] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouse_buttons[event.button.button - 1] = KeyState::KEY_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_buttons[event.button.button - 1] = KeyState::KEY_UP;
			break;

		case SDL_MOUSEMOTION:
			mouse_motion.x = event.motion.xrel / screenSize;
			mouse_motion.y = event.motion.yrel / screenSize;
			mouse.x = event.motion.x / screenSize;
			mouse.y = event.motion.y / screenSize;
			break;
		}
	}

	return true;
}
