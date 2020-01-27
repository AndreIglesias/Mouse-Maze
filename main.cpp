#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char const *argv[])
{

	const int FPS = 35;								//*-
	const int frameDelay = 1000/FPS;				//*-

	Uint32 frameStart;								//*-
	int frameTime;									//*-

	game = new Game();
	do{
		game->init("L4bt0._3xpl0its.wmv", 800, 600, false, argv);

		while (game->running()){

			frameStart = SDL_GetTicks();				//*-

			game->events();
			game->update();
			game->render();

			frameTime = SDL_GetTicks() - frameStart;	//*-

			if (frameDelay > frameTime) 				//*-
				SDL_Delay(frameDelay - frameTime);
		}
	game->Default();
	}while(game->deNuevo()); // jugar de nuevo
	// queres volver a jugar? :v
	game->clean();
	return 0;
}