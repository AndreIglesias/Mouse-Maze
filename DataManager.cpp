#include "DataManager.hpp"
#include <string> 
DataManager::~DataManager(){}
	
bool DataManager::Log()
{
	while(!PARTIDA && !login->isLogged()) // lo mismo que en el main
	{
		login->events();
		login->update();
		login->render();
		if (login->quit())
			break;
	}

	login->clean();
	do{
		settings->clean();
		while(!menu->option())
		{
			menu->events();
			menu->update();
			menu->render();
			if (menu->quit())
				break;
		}
		while(menu->customization() && !settings->goBack())
		{
			settings->events();
			settings->update();
			settings->render();
			if (settings->quit())
				break;
		}
		menu->clean();
	}while(settings->goBack());
	modalidad = menu->eleccion();
	SDL_StopTextInput();
	return login->quit() || menu->quit() || settings->quit();
}

void DataManager::top10(){}

void DataManager::agregarPartida(Jugador player)
{
	std::string x, y, pasos, command;
	x = std::to_string(player.x[player.partidas]);
	y = std::to_string(player.y[player.partidas]);
	pasos = std::to_string(player.pasos[player.partidas]);
	command = "./lista " + player.jugador + " " + x +" " + y + " " + pasos + " " + player.laberinto[player.partidas];
	system(command.c_str());

}