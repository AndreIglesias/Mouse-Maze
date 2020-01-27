#pragma once
#include "Game.hpp"
#include "vec2D.hpp"

class Map
{
public:
	Map();
	Map(std::vector< std::vector<int> >, std::string);
	~Map();

	void LoadMap(std::vector< std::vector<int> >);
	void DrawMap();
	bool DrawMap(double, double, int);
	bool solveMap(int, int);
	void DrawSol();
	vec2D coord2maze(int, int);

	double getWidth() { return width; }
	double getHeight() { return height; }
	std::vector< int > Ruta() { return gruta; }
	std::vector< std::vector<int> > getMap() { return map; }
	int Pasos() { return pasos; }
	bool RutaEncontrada() { return rutaEncontrada; }
	bool Ganaste() { return ganaste; }

private:
	double width = 32, height = 32;
	SDL_Rect src, dest;
	SDL_Texture* camino;
	SDL_Texture* walls;
	SDL_Texture* Recorrido;
	SDL_Texture* Queso;
	std::vector< std::vector<int> > map, solution;
	std::vector< int > gruta;
	int pasos = 0;
	bool ganaste = false;
	bool rutaEncontrada = false;
};