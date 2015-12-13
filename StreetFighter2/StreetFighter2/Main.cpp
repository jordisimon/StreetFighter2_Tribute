#include <stdlib.h>
#include "Defines.h"
#include "Game.h"
#include "Entity.h"

/**
WARNING!!!
Para poder compilar este proyecto en VS 2015, ha sido necesario recompilar el proyecto SDL2main.lib con esta misma version de Visual Studio.
En la carpeta SDL/libx86/ se puede encontrar ahora mismo los archivos:
SDL2main_VC2013.lib y
SDL2main_VC2015.lib
Hay que copiar y renombrar a SDL2main.lib la que corresponda segun la versión de Visual Studio que queramos usar.
*/

#include "SDL/include/SDL.h"
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
			game = CreateGame();
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
			Entity::Result update_return = game->Update();

			if (update_return == Entity::Result::R_ERROR)
			{
				LOG("Game Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == Entity::Result::R_EXIT)
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