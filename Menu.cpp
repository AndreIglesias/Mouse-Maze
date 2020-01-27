#include "Menu.hpp"
#include "Game.hpp"
#include <unistd.h>

positions y;
positions yy;


void Menu::events()
{
	SDL_PollEvent(&Game::event);
	switch(Game::event.type){
		case SDL_QUIT:
			Quit = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			switch(Game::event.button.button)
			{
			case SDL_BUTTON_LEFT:
				usleep(5000);
				int x, y;
				SDL_GetMouseState(&x, &y);
				if(x < 710 && x > 470 &&
					y < 470 && y > 405)
				{/*ajustes*/
					custo = true;
					op = true;
				}
				if(x < 335 && x > 90 &&
					y < 470 && y > 405)
				{/*manual*/
					elejido = 0;
					op = true;
				}
				if(x < 335 && x > 90 &&
					y < 220 && y > 150)
				{/*automatico*/
					elejido = 1;
					op = true;
				}
				if(x < 710 && x > 470 &&
					y < 220 && y > 150)
				{/*cpu*/
					elejido = 2;
					op = true;
				}

				if(x < 760 && x > 702 &&
					y < 44 && y > 18)
				{/*help*/
					system("rifle documentacion/manual.pdf &");
				}
				
				break;
			case SDL_BUTTON_RIGHT:
				std::cout << "right";
				break;
			case SDL_BUTTON_X1:
				std::cout << "X1";
				break;
			}
			break;
		}
		default:
			break;
	}
}
void Menu::update() 
{
	if(comenzar)
		init(Path);
	y.h2 = 70;
	y.w2 = 245;
	ButtMan->update(y);
	ButtMan->update(y);
	ButtAuto->update(y);
	ButtSettings->update(y);
	ButtVs->update(y);
	yy.h2 = 28;
	yy.w2 = 60;
	help->update(yy);
}
void Menu::render()
{
	SDL_RenderClear(Game::renderer);
	fondo->render(false, false);
	ButtMan->render(false, true);
	ButtAuto->render(false, true);
	ButtSettings->render(false, true);
	ButtVs->render(false, true);
	help->render(false, true);

	TextureManager::DrawDest(autoTex, autoR);
	TextureManager::DrawDest(manTex, manualR);
	TextureManager::DrawDest(versusTex, versusR);
	TextureManager::DrawDest(settingsTex, settingsR);

	SDL_RenderPresent(Game::renderer);
}
void Menu::clean() 
{
	SDL_RenderClear(Game::renderer);
	op = false;
	custo = false;
	comenzar = true;
}
