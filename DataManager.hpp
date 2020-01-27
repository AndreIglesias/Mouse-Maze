#pragma once
#include "Game.hpp"
#include "Login.hpp"
#include "Menu.hpp"
#include "Settings.hpp"
 
class DataManager
{
public:
	DataManager()
	{
		partidas.open("datos/partidas.txt");
	}
	DataManager(const char* path0, const char* path1, const char* path2 , bool partida)
	{
		PARTIDA = partida;
		login = new Login(path0);
		menu = new Menu(path1);
		settings = new Settings(path2);
		partidas.open("datos/partidas.txt");
	}
	~DataManager();
	
	bool Log();
	void top10(); //leer archivo
	void agregarPartida(Jugador); //agregar a lista
	int Modalidad(){ return modalidad; }
	std::string playerName() { return login->playerName();}
	std::string laberinto() { return "laberintos/"+settings->laberinto(); }
	std::string textura() { return settings->textura(); }

private:
	std::ifstream partidas;
	int modalidad;
	Login* login;
	Menu* menu;
	Settings* settings;
	bool PARTIDA;
};
