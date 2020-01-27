#pragma once
#include "Game.hpp"


class Login
{
public:
	Login(){}
	Login(const char* path) 
	{
		Path = path;
		init(Path);
	}
	~Login();
	void init(const char* path)
	{
		fondo = new Object(path, 0, 0);
		logo = new Object("UI/logo.bmp", 68, 20);
		textComponents = TextureManager::loadFromRenderedText(inputText.c_str(), textColor, Font);
		SDL_StartTextInput();
		inputDest = { 225, 370, textComponents.width, textComponents.height };
		texture = textComponents.texture;

		textComponents = TextureManager::loadFromRenderedText(login.c_str(), logColor, Font);
		logDest = { 40, 370, textComponents.width, textComponents.height };
		logTexture = textComponents.texture;

		textbox = new Object("UI/widgets/textbox.bmp", 40, 70);
		comenzar = false;
	}
	void events();
	void update();
  	void render();
  	void clean();
  	bool quit() { return Quit; }

	bool isLogged() { return Logged; }
	std::string playerName() { return inputText; }

private:
	bool Logged = false, renderText = false, Quit = false;
	bool comenzar = true;
	const char* Path;
	Object* fondo;
	SDL_Texture* texture;
	SDL_Texture* logTexture;
	texto textComponents;
	std::string inputText = "HOLA";
	std::string login = "Nombre";
	SDL_Color textColor = { 0, 0, 0, 0 }, logColor = {128, 128, 128, 128}; // text color
	SDL_Rect inputDest = { 0, 0, 128, 32 }, logDest = { 200, 150, 128, 40 };
	TTF_Font *Font = TTF_OpenFont( "UI/ttf/slkscrb.ttf", 28 );		// fuente global
	Object* textbox;
	Object* logo;
	std::string validar;
};