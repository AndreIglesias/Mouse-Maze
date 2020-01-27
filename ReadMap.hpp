#pragma once
#include "Game.hpp"

class ReadMap
{
public:
	ReadMap(char const *argv[]);
	~ReadMap();
  void Read(char const *argv[]);

	bool exist(){return existMap;}
  std::vector< std::vector<int> > getMap(){return map;}

  std::string labto() { return laberinto; }

private:
	std::ifstream file;
	bool existMap = false;
	std::string laberinto;
  std::vector< std::vector<int> > map;
};