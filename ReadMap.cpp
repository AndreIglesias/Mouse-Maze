#include "ReadMap.hpp"
#include <stdlib.h>
#include <string.h>

void replace(std::string& str, const std::string& from, const std::string& to)
{                                                         
  if(from.empty())                                                                                                        
    return;                                                                         
  size_t start_pos = 0;                                                                                                   
  while((start_pos = str.find(from, start_pos)) != std::string::npos) {                                                        
    str.replace(start_pos, from.length(), to);                                                                            
    start_pos += to.length();                                                                                             
  }                                                                                                                       
}



ReadMap::ReadMap(char const *argv[]){ Read(argv); }

ReadMap::~ReadMap(){}

void ReadMap::Read(char const *argv[])
{
	std::string out;
	std::vector <int> vec;
	file.open(argv[1]);
	int aux;

  if(strlen(argv[2])!=1)
    argv[2] = " ";
  if(strlen(argv[3])!=1)
    argv[3] = "#";
  if(strlen(argv[4])!=1)
    argv[4] = "Q";

	if (file.is_open())
	{
    laberinto = argv[1];
    	while (!file.eof())
    	{
      		getline(file,out); 
      		replace(out, argv[2], " 0 "); //" "
      		replace(out, argv[3], " 1 "); //"#"
          replace(out, argv[4], " 2 "); //"Q"
      		std::stringstream iss (out);
      		while (iss >> aux)
      			vec.push_back(aux);
      		map.push_back(vec);
      		vec.clear();
    	}
    	existMap = true;
  	}  
  	else
  	{
  		std::cout << "No se ha abierto nada\n... generando laberinto al azar" << std::endl;
  		system("./generator 25 21 > laberintos/randomMazes.txt");
  		argv[1] = "laberintos/randomMazes.txt";
  		Read(argv);
  	}

  	file.close();
}
