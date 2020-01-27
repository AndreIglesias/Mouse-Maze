#pragma once
#include "Game.hpp"


class Menu
{
public:
	Menu(){}
	Menu(const char* path) //SDL_Renderer* renderer, SDL_Event event, 
	{
		Path = path;
		init(Path);
	}
	~Menu();
	void init(const char* path)
	{
		fondo = new Object(path, 0, 0);
		help = new Object("UI/widgets/help.bmp", 140, 3);
		
		textComponents = TextureManager::loadFromRenderedText(autom.c_str(), textColor, Font); //automatico button
		autoR = { 103, 168, textComponents.width, textComponents.height };
		autoTex = textComponents.texture;

		textComponents = TextureManager::loadFromRenderedText(manual.c_str(), textColor, Font); // manual button
		manualR = { 135, 420, textComponents.width, textComponents.height };
		manTex = textComponents.texture;

		textComponents = TextureManager::loadFromRenderedText(versus.c_str(), textColor, Font); // versus button
		versusR = { 515, 168, textComponents.width, textComponents.height };
		versusTex = textComponents.texture;

		textComponents = TextureManager::loadFromRenderedText(settings.c_str(), textColor, Font); // settings button
		settingsR = { 505, 420, textComponents.width, textComponents.height };
		settingsTex = textComponents.texture;

		ButtAuto = new Object("UI/widgets/button.bmp", 18, 30);
		ButtMan = new Object("UI/widgets/button.bmp", 18, 80);
		ButtVs = new Object("UI/widgets/button.bmp", 93, 30);
		ButtSettings = new Object("UI/widgets/button.bmp", 93, 80);
		comenzar = false;
	}
	void events();
	void update();
  	void render();
  	void clean();
  	bool quit() { return Quit; }

	bool option() { return op; }
	bool customization() { return custo; }
	int eleccion(){ return elejido; }

private:
	bool op = false, custo = false, Quit = false;
	bool comenzar = true;
	const char* Path;
	Object* fondo;
	SDL_Texture* autoTex;
	SDL_Texture* manTex;
	SDL_Texture* versusTex;
	SDL_Texture* settingsTex;

	texto textComponents;
	std::string autom = "Automatico";
	std::string manual = "Manual";
	std::string versus = "VS CPU";
	std::string settings = "Ajustes";

	SDL_Color textColor = { 0, 0, 0, 0 }; // text color
	SDL_Rect autoR, manualR, versusR, settingsR;
	TTF_Font *Font = TTF_OpenFont( "UI/ttf/slkscrb.ttf", 27 );		// fuente global
	//buttons
	Object* ButtMan;
	Object* ButtAuto;
	Object* ButtVs;
	Object* ButtSettings;
	Object* help;

	int elejido;
};