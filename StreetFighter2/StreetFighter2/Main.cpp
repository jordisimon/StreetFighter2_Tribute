#include <stdlib.h>
#include "Defines.h"
#include "Game.h"
#include "Module.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL/libx86/SDL2_image.lib" )
#pragma comment( lib, "SDL/libx86/SDL2_mixer.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Game* game = nullptr;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("Game Creation --------------");
			game = new Game();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("Game Init --------------");
			if (game->Init() == false)
			{
				LOG("Game Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("Game Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			Module::Update_result update_return = game->Update();

			if (update_return == Module::Update_result::UPDATE_ERROR)
			{
				LOG("Game Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == Module::Update_result::UPDATE_EXIT)
				state = MAIN_FINISH;
		}
		break;

		case MAIN_FINISH:

			LOG("Application CleanUp --------------");
			if (game->CleanUp() == false)
			{
				LOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	RELEASE(game);
	LOG("Bye :)\n");
	return main_return;
}