#include "ServiceInput.h"
#include "Defines.h"
#include "Config.h"
#include "SDL\include\SDL.h"


ServiceInput::ServiceInput()
{
	memset(keyboard, (int)KeyState::KEY_IDLE, sizeof(KeyState) * MAX_KEYBOARD_KEYS);
	memset(mouse_buttons, (int)KeyState::KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
	memset(gameController1, (int)KeyState::KEY_IDLE, sizeof(KeyState) * SDL_CONTROLLER_BUTTON_MAX);
	memset(gameController2, (int)KeyState::KEY_IDLE, sizeof(KeyState) * SDL_CONTROLLER_BUTTON_MAX);
}

bool ServiceInput::Init()
{
	LOG("Init Input Service");

	screenSize = config->LoadIntValue("Render", "screenRatio", "2");

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_GAME_CONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (SDL_InitSubSystem(SDL_INIT_HAPTIC) < 0)
	{
		LOG("SDL_HAPTIC could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	int numJoySticks = SDL_NumJoysticks();
	if (numJoySticks > 0)
	{
		if (SDL_IsGameController(0))
		{
			controller1 = SDL_GameControllerOpen(0);
			haptic1 = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(controller1));
		}
	}

	if (numJoySticks > 1)
	{
		if (SDL_IsGameController(1))
		{
			controller2 = SDL_GameControllerOpen(1);
			haptic2 = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(controller2));
		}
	}

	return true;
}

bool ServiceInput::CleanUp()
{
	LOG("CleanUp Input Service");
	SDL_HapticClose(haptic2);
	SDL_GameControllerClose(controller2);
	SDL_HapticClose(haptic1);
	SDL_GameControllerClose(controller1);
	
	SDL_QuitSubSystem(SDL_INIT_HAPTIC);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
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

	UpdateGameControllerState(controller1, gameController1);
	UpdateGameControllerState(controller2, gameController2);

	return true;
}


void ServiceInput::UpdateGameControllerState(SDL_GameController* controller, KeyState* controllerState)
{
	/*for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)i))
		{
			if (controllerState[i] == KeyState::KEY_IDLE)
				controllerState[i] = KeyState::KEY_DOWN;
			else
				controllerState[i] = KeyState::KEY_REPEAT;
		}
		else
		{
			if (controllerState[i] == KeyState::KEY_REPEAT || controllerState[i] == KeyState::KEY_DOWN)
				controllerState[i] = KeyState::KEY_UP;
			else
				controllerState[i] = KeyState::KEY_IDLE;
		}
	}*/

	//Managing diagonals
	bool tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_MAX];

	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		tempStates[i] = SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)i) != 0;
	}

	tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_UP_LEFT] = false;
	tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_UP_RIGHT] = false;
	tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN_LEFT] = false;
	tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN_RIGHT] = false;

	if (tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_UP] && tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT])
	{
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_UP_LEFT] = true;
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_UP] = false;
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT] = false;
	} 
	else if (tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_UP] && tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT])
	{
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_UP_RIGHT] = true;
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_UP] = false;
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT] = false;
	}
	else if (tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN] && tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT])
	{
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN_LEFT] = true;
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN] = false;
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT] = false;
	}
	else if (tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN] && tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT])
	{
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN_RIGHT] = true;
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN] = false;
		tempStates[(int)GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT] = false;
	}

	for (int i = 0; i < (int)GameControllerButton::CONTROLLER_BUTTON_MAX; ++i)
	{
		if (tempStates[i])
		{
			if (controllerState[i] == KeyState::KEY_IDLE)
				controllerState[i] = KeyState::KEY_DOWN;
			else
				controllerState[i] = KeyState::KEY_REPEAT;
		}
		else
		{
			if (controllerState[i] == KeyState::KEY_REPEAT || controllerState[i] == KeyState::KEY_DOWN)
				controllerState[i] = KeyState::KEY_UP;
			else
				controllerState[i] = KeyState::KEY_IDLE;
		}
	}

}
