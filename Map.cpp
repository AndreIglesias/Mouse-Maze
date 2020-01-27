#include "Map.hpp"
#include "Game.hpp"
#include <stdlib.h>
#include "Algorithms.hpp"
#include "vec2D.hpp"
#include <unistd.h>

Map::Map(){}

Map::~Map()
{
	SDL_DestroyTexture(camino);
	SDL_DestroyTexture(walls);
	SDL_DestroyTexture(Recorrido);
	SDL_DestroyTexture(Queso);
}

Map::Map(std::vector< std::vector<int> > lvl, std::string textura){

	camino = TextureManager::LoadTexture("images/piso2.bmp");
	walls = TextureManager::LoadTexture(textura.c_str());
	Recorrido = TextureManager::LoadTexture("images/Ground.bmp");
	Queso = TextureManager::LoadTexture("UI/Queso.bmp");
	LoadMap(lvl);
	//std::cout << lvl.size() << "-" << lvl[0].size() << std::endl;

	width = 800/(int)lvl[0].size(); 						//grosor de la ventana/grosor del laberinto (double es para hacer division real)
	height = 600/(int)lvl.size();						//altura de la ventana/altura del laberinto 
	//dejar como opcion si el laberinto estar en toda la ventana o si tenga una continuidad mas suave haciendo division entera.

	//std::cout << width << "--" << height << std::endl;

	src.x = src.y = 20;
	src.w = dest.w = width;
	src.h = dest.h = height;
	dest.x = dest.y = 20;

}


void Map::LoadMap(std::vector< std::vector<int> > labyrinth){
	for (int row = 0; row < labyrinth.size(); row++)
		map.push_back(labyrinth[row]);
}

vec2D Map::coord2maze(int x, int y)
{
	for (int row = 0; row < map.size(); row++)
	{
		for (int col = 0; col < map[row].size(); ++col)
		{

			dest.x = col*width;
			dest.y = row*height;

			//AABB collision detection
			if( x+width/2 > dest.x && x+width/2 < dest.x + width &&
				y+height/2 > dest.y && y+height/2 < dest.y + height )
				return vec2D(row, col);
		}
	}
}


void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < map.size(); row++)
	{
		for (int col = 0; col < map[row].size(); ++col)
		{	
			type = map[row][col];

			dest.x = col*width;
			dest.y = row*height;

			switch (type)
			{
				case 0:
					//TextureManager::Draw(camino, src, dest);
					TextureManager::DrawDest(camino, dest);	
					break;
				case 1:
					//TextureManager::Draw(walls, src, dest);
					TextureManager::DrawDest(walls, dest);	
					break;
				case 2:
					TextureManager::DrawDest(camino, dest);	
					TextureManager::DrawDest(Queso, dest);
					break;
			}
		}
	}
}

bool Map::DrawMap(double x, double y, int scale) //centro del raton
{
	int type = 0;
	bool enRect, choco = false;
	for (int row = 0; row < map.size(); row++)
	{
		for (int col = 0; col < map[row].size(); ++col)
		{
			type = map[row][col];

			dest.x = col*width;
			dest.y = row*height;

			//AABB collision detection
			if( x > dest.x && x < dest.x + width &&
				y > dest.y && y < dest.y + height )
				enRect = true;
			else
				enRect = false;
			switch (type)
			{
				case 0:
					if(enRect)
						TextureManager::DrawDest(Recorrido, dest);
					else
						TextureManager::DrawDest(camino, dest);	
					break;
				case 1:
					TextureManager::DrawDest(walls, dest);
					if(enRect)
						choco = true;
					break;
				case 2:
					if(enRect)
						ganaste = true;
					TextureManager::DrawDest(camino, dest);	
					TextureManager::DrawDest(Queso, dest);
					break;
			}
		}
	}
	return choco;
}

//------------------------------------------------------------------------
bool Map::solveMap(int x, int y)
{
	int i, j;
	vec2D vec = coord2maze(x, y);
	i = vec.x;
	j = vec.y;
	Algorithms solver(map);
	rutaEncontrada = solver.DepthFirst(i, j);
	solution = solver.getMap();
	gruta = solver.ruta();
	solver.clean();
	if(!rutaEncontrada)
		std::cout << "Ruta no encontrada..." << std::endl;

	return map[i][j] == 0;
}

void Map::DrawSol()
{	
	bool yaContados = false;
	if(pasos!=0)
		yaContados = true;
	int type = 0;
	for (int row = 0; row < solution.size(); row++)
	{
		for (int col = 0; col < solution[row].size(); col++)
		{

			type = solution[row][col];

			dest.x = col*width;
			dest.y = row*height;

			switch (type)
			{
				case 0:
					TextureManager::DrawDest(camino, dest);	
					break;
				case 1:
					TextureManager::DrawDest(walls, dest);	
					break;
				case 2:
					TextureManager::DrawDest(camino, dest);	
					TextureManager::DrawDest(Queso, dest);
					break;
				case 3:
					if(!yaContados)
						pasos++;
					TextureManager::DrawDest(Recorrido, dest);
					break;
				case 5:
					TextureManager::DrawDest(Recorrido, dest);	
					TextureManager::DrawDest(Queso, dest);
					break;
			}
		}
	}
}

