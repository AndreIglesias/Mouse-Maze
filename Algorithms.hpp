#include "Game.hpp"

class Algorithms
{
public:
	Algorithms(std::vector< std::vector<int> >);
	void Dijsktra();
	void RHrule();
	bool DepthFirst(int, int);
	std::vector< int > ruta() { return solucion; }

	void clean()
	{
		//Recorrido.clear();
		//Camino.clear();
	}
	std::vector< std::vector<int> > getMap() { return map; }

private:
	std::vector< std::vector<int> > map;
	std::vector< int > solucion;
};


Algorithms::Algorithms(std::vector< std::vector<int> > labyrinth){
	for (int row = 0; row < labyrinth.size(); row++)
		map.push_back(labyrinth[row]);
}

bool Algorithms::DepthFirst(int x, int y)
{
    if(map[x][y]==2)
    {
        map[x][y] = 5;
        solucion.push_back(x);
        solucion.push_back(y);
        return true;
    }
 
    if(x >= 0 && x < map.size() && y >= 0 && y < map[0].size() && map[x][y] == 0)
    {
        map[x][y] = 3;
        solucion.push_back(x);
        solucion.push_back(y);
 
        if (DepthFirst(x+1, y))
            return true;

        if (DepthFirst(x, y+1))
            return true;

        if (DepthFirst(x, y-1))
            return true;

        if (DepthFirst(x-1, y))
            return true;

 		map[x][y] = 0;
 		solucion.pop_back();
 		solucion.pop_back();
        return false; // si se quedo atrapado
    }   
 
    return false;
}