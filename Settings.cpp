#include "Settings.hpp"
#include "Game.hpp"
#include <unistd.h>

positions z;
positions zz;


void Settings::events()
{
	SDL_PollEvent(&Game::event);
	switch(Game::event.type){
		case SDL_QUIT:
			Quit = true;
			break;
		
		case SDL_KEYDOWN:
			
			if( Game::event.key.keysym.sym == SDLK_DELETE && inputText.length() > 0 )
			{
				back = true;
			}			
			else if ( Game::event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 ) 
			{
				inputText.pop_back();
				renderText = true;
				usleep(130000);
			}
			//Handle copy
			else if( Game::event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
			{
				SDL_SetClipboardText( inputText.c_str() );
			}
			//Handle paste
			else if( Game::event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
			{
				inputText = SDL_GetClipboardText();
				renderText = true;
			}
			break;

		case SDL_TEXTINPUT:
			if( !( ( Game::event.text.text[ 0 ] == 'c' || Game::event.text.text[ 0 ] == 'C' ) 
				&& ( Game::event.text.text[ 0 ] == 'v' || Game::event.text.text[ 0 ] == 'V' ) 
				&& SDL_GetModState() & KMOD_CTRL ) )
			{
				if(inputText.length() < 16)
				{
					validar = Game::event.text.text;
					if(validar != " ")
					{
						inputText += Game::event.text.text;
						renderText = true;
						usleep(130000);
					}
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			switch(Game::event.button.button)
			{
			case SDL_BUTTON_LEFT:
				usleep(5000);
				int x, y;
				SDL_GetMouseState(&x, &y);

				if(x < 202 && x > 100 &&
					y < 202 && y > 103)
				{/*verde*/
					std::cout << "aa"<< std::endl;
					texturaElegida = "images/paredcita.bmp";
					back = true;

				}
				if(x < 700 && x > 600 &&
					y < 200 && y > 102)
				{/*ground*/
					std::cout << "aa"<< std::endl;
					texturaElegida = "images/Ground.bmp";
					back = true;
				}
				if(x < 200 && x > 100 &&
					y < 528 && y > 428)
				{/*Index*/
					std::cout << "aa"<< std::endl;
					texturaElegida = "images/index.bmp";
					back = true;
				}
				if(x < 700 && x > 600 &&
					y < 528 && y > 428)
				{/*cpu*/
					std::cout << "aa"<< std::endl;
					texturaElegida = "images/piso.bmp";
					back = true;
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
void Settings::update() 
{
	if(comenzar)
		init(Path);
	if( renderText )
	{
		//Text is not empty
		if( inputText != "" )
		{
			//Render new text
			textComponents = TextureManager::loadFromRenderedText( inputText.c_str(), textColor, Font );
			inputDest = { 225, 370, textComponents.width, textComponents.height };
			texture = textComponents.texture;
		}
		//Text is empty
		else
		{
			//Render space texture
			textComponents = TextureManager::loadFromRenderedText( " ", textColor, Font );
			inputDest = { 300, 450, textComponents.width, textComponents.height };
			texture = textComponents.texture;
		}
	}
	textbox->update(z);
	zz.h2 = 100;
	zz.w2 = 128;
	logo->update(zz);
	zz.h2 = zz.w2 = 100;
	tex1->update(zz);
	tex2->update(zz);
	tex3->update(zz);
	tex4->update(zz);
}
void Settings::render()
{
	SDL_RenderClear(Game::renderer);
	fondo->render(false, false);
	logo->render(false, true);

	textbox->render(false, true);
	tex1->render(false, true);
	tex2->render(false, true);
	tex3->render(false, true);
	tex4->render(false, true);
	TextureManager::DrawDest(texture, inputDest);
	TextureManager::DrawDest(logTexture, logDest);

	SDL_RenderPresent(Game::renderer);
}
void Settings::clean() 
{
	SDL_RenderClear(Game::renderer);
	renderText = false;
	comenzar = true;
	back = false;

}
