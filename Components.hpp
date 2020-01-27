#pragma once
#include "ECS.hpp"
#include "SDL2/SDL.h"
#include "eventHandling.hpp"
#include <iostream>
#include "vec2D.hpp"

class CoordComp : public Component // position/coordenate component
{
public:
	vec2D position, velocity;
	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 2;

	CoordComp(float x, float y) { position.x=x; position.y=y; }
	CoordComp() { position.x=0; position.y=0; }
	void init() { velocity.x=0; velocity.y=0; }
	void update() 
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};



class SpriteComp : public Component
{
public:
	SpriteComp() = default;
	SpriteComp(const char* path) { setTex(path); Path = path; }			 		//textura del componente sprite de la entidad
	void setTex(const char* path) { texture = TextureManager::LoadTexture(path); Path = path; } //Cambia textura de la entidad
	void init() ;
	void update() ;
	void draw() ;

private:
	CoordComp *coord;
	SDL_Texture *texture;
	SDL_Rect sourceR, destR;
	const char* Path;
	int contador = 0;

};

//-------------------------------------------------

void SpriteComp::init() 
{
	coord = &entity->getComp<CoordComp>(); //posicion de la entidad

	sourceR.x = sourceR.y = 0;
	sourceR.w = coord->width;
	sourceR.h = coord->height;
	destR.w = coord->width*coord->scale;
	destR.h = coord->height*coord->scale;
}

void SpriteComp::update()  
{
	destR.x = (int)coord->position.x; // int porque el rectangulo espera un entero
	destR.y = (int)coord->position.y;
}

void SpriteComp::draw()
{
	//TextureManager::Draw(texture, sourceR, destR);
	TextureManager::DrawDest(texture, destR);
}




//-------------------------------------------------
// Componentes interactivos

class Keyboard : public Component
{

private:
	bool up=false, dw=false, lf=false, rg=false;		//sprites
	bool U=true, D=false, L=false, R=false;				//historial
	bool cu = false, cd = false, cl = false, cr = false; //colision

public:
	CoordComp *coord;
	SpriteComp *sprite;

	int direccion()
	{
		if(U)
			return 8;
		if(D)
			return 2;
		if(L)
			return 4;
		if(R)
			return 6;
		return 0;
	}

	void init() 
	{
		coord = &entity->getComp<CoordComp>();
		sprite = &entity->getComp<SpriteComp>();
	}

	void resetChoques(){cu = false, cd = false, cl = false, cr = false;}
	void chocoUp(){cu = true;}
	void chocoDw(){cd = true;}
	void chocoLf(){cl = true;}
	void chocoRg(){cr = true;}

	void update()
	{
		switch(Game::event.type)
		{
			case SDL_KEYDOWN:
			{
				switch(Game::event.key.keysym.sym)
				{
					case SDLK_w:
						if(!cu)
						{
							coord->velocity.y = -1;
							if(up) 
							{
								sprite->setTex("UI/personajes/raton/arriba1.bmp");
								up = false;
							}
							else 
							{
								sprite->setTex("UI/personajes/raton/arriba2.bmp");
								up = true;
							}
							U = true;
							D = L = R = false;
						}
						break;
					case SDLK_a:
						if(!cl)
						{
							coord->velocity.x = -1;
							if(lf)
							{
								sprite->setTex("UI/personajes/raton/izquierda1.bmp");
								lf = false;
							} 
							else 
							{
								sprite->setTex("UI/personajes/raton/izquierda2.bmp");
								lf = true;
							}
							L = true;
							U = D = R = false;
						}
						break;
					case SDLK_s:
						if(!cd)
						{
							coord->velocity.y = 1;
							if(dw) 
							{
								sprite->setTex("UI/personajes/raton/abajo1.bmp");
								dw = false;
							}
							else 
							{
								sprite->setTex("UI/personajes/raton/abajo2.bmp");
								dw = true;
							}
							D = true;
							L = U = R = false;
						}
						break;
					case SDLK_d:
						if(!cr)
						{
							coord->velocity.x = 1;
							if(rg) 
							{
								sprite->setTex("UI/personajes/raton/derecha1.bmp");
								rg = false;
							}
							else 
							{
								sprite->setTex("UI/personajes/raton/derecha2.bmp");
								rg = true;
							}
							R = true;
							L = D = U = false;
						}
						break;
				}
				break;
			}
			case SDL_KEYUP:
			{
				switch(Game::event.key.keysym.sym)
				{
					case SDLK_w:
						coord->velocity.y = 0;
						break;
					case SDLK_a:
						coord->velocity.x = 0;
						break;
					case SDLK_s:
						coord->velocity.y = 0;
						break;
					case SDLK_d:
						coord->velocity.x = 0;
						break;
				}
				break;
			}
		}
	}
	
};