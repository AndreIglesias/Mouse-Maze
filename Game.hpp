#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */


  typedef struct p
  {
    int X = 0, Y = 0;
    int h1 = 64, w1 = 64, x1 = 0, y1 = 0;
    int h2 = 70, w2 = 400, x2 = 1, y2 = 1;
  } positions;

struct texto
{
  int width, height;
  SDL_Texture* texture;
};

struct Jugador
{
  std::vector < long int > x, y, pasos;
  std::vector < std::string > laberinto;
  std::string jugador;
  int partidas = 0;
};

//--------------------------------------------------------------------------------------------

class Game {

public:
  Game();
  ~Game();

  void init( const char* title, int width, int height, bool fullScreen, char const *argv[] );

  void events();
  void update();
  void render();
  void clean();

  bool running(){ return isRunning; }
  bool raton() { return isRaton; }
  bool deNuevo() { return nuevaPartida; }

  void Default()
  {
    isRaton = automatico = cpu = isRunning = false;
    gano = WIN = LOSE = false;
    nuevo = posY = 0;
    posX = 1;
    cont = 0;
  }

  static SDL_Renderer* renderer;
  static SDL_Event event;

private:
  bool isRaton = false;
  bool automatico = false;
  bool cpu = false;
  bool isRunning, gano = false;
  SDL_Window* window;
  int cont = 0;
  int initX, initY;
  int posX=1, posY=0;
  bool existeRuta = true;
  bool WIN = false, LOSE = false;
  bool nuevaPartida = false;
  int nuevo = 0;
  time_t now;
  time_t after;
  bool mostrado = false;
  Mix_Music *music = NULL;
};


//--------------------------------------------------------------------------------------------
//
class TextureManager
{
public:
  // static method
  static SDL_Texture* LoadTexture(const char* file){
    SDL_Surface* tmpSurface = SDL_LoadBMP(file); //IMG_Load(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
  }
  static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);  // porcion
  }
  static void DrawSrc(SDL_Texture* tex, SDL_Rect src){
    SDL_RenderCopy(Game::renderer, tex, &src, NULL);   // porcion agrandada
  }
  static void DrawDest(SDL_Texture* tex, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, tex, NULL, &dest); // Imagen ajustada
  }
  static void DrawNull(SDL_Texture* tex){
    SDL_RenderCopy(Game::renderer, tex, NULL, NULL); // Pantalla completa
  }
  static texto loadFromRenderedText( std::string, SDL_Color, TTF_Font*);
};


//--------------------------------------------------------------------------------------------

class Object
{
public:
  Object(const char* texture, int x, int y);
  ~Object();

  void update(positions pos);
  void render(bool sr, bool dr);
  positions pos;
private:
  int x;
  int y;
  SDL_Texture* objTex;
  SDL_Rect sourceR, destinationR; //source rect, destination rect
  
};


#endif
