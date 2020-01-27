#pragma once
#include "Game.hpp"


class Settings
{
public:
	Settings(){}
	Settings(const char* path) //SDL_Renderer* renderer, SDL_Event event, 
	{
		Path = path;
		init(Path);
	}
	~Settings();
	void init(const char* path)
	{
		fondo = new Object(path, 0, 0);
		logo = new Object("UI/logo.bmp", 68, 20);
		tex1 = new Object("images/paredcita.bmp", 20,20);
		tex2 = new Object("images/piso.bmp", 120, 85);
		tex3 = new Object("images/index.bmp", 20, 85);
		tex4 = new Object("images/Ground.bmp", 120, 20);
		textComponents = TextureManager::loadFromRenderedText(inputText.c_str(), textColor, Font);
		SDL_StartTextInput();
		inputDest = { 225, 370, textComponents.width, textComponents.height };
		texture = textComponents.texture;

		textComponents = TextureManager::loadFromRenderedText(login.c_str(), logColor, Font);
		logDest = { 300, 450, textComponents.width, textComponents.height };
		logTexture = textComponents.texture;

		textbox = new Object("UI/widgets/textbox.bmp", 40, 70);
		comenzar = false;
	}
	void events();
	void update();
  	void render();
  	void clean();
  	bool goBack() { return back; }
  	bool quit() { return Quit; }
  	std::string laberinto() { return inputText; }
  	std::string textura() { return texturaElegida; }
private:
	bool renderText = false, Quit = false, back = false;
	bool comenzar = true;
	const char* Path;
	Object* fondo;
	SDL_Texture* texture;
	SDL_Texture* logTexture;
	texto textComponents;
	std::string inputText = "labto";
	std::string login = "Laberinto";
	SDL_Color textColor = { 0, 0, 0, 0 }, logColor = {128, 128, 128, 128}; // text color
	SDL_Rect inputDest = { 0, 0, 128, 32 }, logDest = { 200, 150, 128, 40 };
	TTF_Font *Font = TTF_OpenFont( "UI/ttf/slkscrb.ttf", 28 );		// fuente global
	Object* textbox;
	Object* logo;
	std::string validar;
	Object* tex1;
	Object* tex2;
	Object* tex3;
	Object* tex4;
	std::string texturaElegida = "images/pared.bmp";

};