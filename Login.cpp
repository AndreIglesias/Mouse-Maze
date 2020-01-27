#include "Login.hpp"
#include "Game.hpp"
#include <unistd.h>

positions x;
positions xx;


void Login::events()
{
	SDL_PollEvent(&Game::event);
	switch(Game::event.type){
		case SDL_QUIT:
			Quit = true;
			break;
		
		case SDL_KEYDOWN:
			if( Game::event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
			{
				//lop off character
				inputText.pop_back();
				renderText = true;
				usleep(130000);
			}
			if( Game::event.key.keysym.sym == SDLK_RETURN && inputText.length() > 0 )
			{
				Logged = true;
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
				//Append character
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
				int x, y;
				SDL_GetMouseState(&x, &y);
				//if(true)
					//Logged = true;
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
void Login::update() 
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
			inputDest = { 225, 370, textComponents.width, textComponents.height };
			texture = textComponents.texture;
		}
	}
	textbox->update(x);
	xx.h2 = 100;
	xx.w2 = 128;
	logo->update(xx);
}
void Login::render()
{
	SDL_RenderClear(Game::renderer);
	fondo->render(false, false);
	logo->render(false, true);

	textbox->render(false, true);
	TextureManager::DrawDest(texture, inputDest);
	TextureManager::DrawDest(logTexture, logDest);

	SDL_RenderPresent(Game::renderer);
}
void Login::clean() 
{
	SDL_RenderClear(Game::renderer);
	comenzar = true;
}
