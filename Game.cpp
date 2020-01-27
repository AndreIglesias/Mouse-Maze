#include "Game.hpp"
#include "Map.hpp"
#include "ReadMap.hpp"
#include "DataManager.hpp"

#include "ECS.hpp"
#include "Components.hpp"
#include "vec2D.hpp"
#include <unistd.h>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Object* fondo;
Object* jugarDenuevo;
Object* Ulose;
Object* Uwin;
Object* Black;

Manager manager;
auto& Raton1(manager.addEntity());

ReadMap* rMap;
Map* map;
DataManager* dataM;

Jugador player;

//--------------------------------------------------------------------------------------------

Game::Game(){}
Game::~Game(){}

void Game::init( const char* title, int width, int height, bool fullScreen, char const *argv[] ){
	if(!nuevaPartida)
	{
		int flags = 0; //verifica si fullscreen para pasarlo en argumentos de la creacion de la ventana
		if(fullScreen)
			flags = SDL_WINDOW_FULLSCREEN;
		if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

			if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
				std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;

			window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //(-1 index) and (0 flags)

			if(!renderer)
				std::cout << "Renderer not created" << std::endl;
			else
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

			if(!window)
				std::cout << "Window not created" << std::endl;

			isRunning = true;
		}	
		else
			isRunning = false;
		
		if( TTF_Init() == -1 )
		{
			std::cout << "TTF not created" << std::endl;
			isRunning = false;
		}
		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1 ) { isRunning = false; }
		//SDL_WM_SetCaption( "Monitor Music", NULL );
		system("rifle music.webm &");
		//music = Mix_LoadMUS( "music.webm" );
		//Mix_PlayMusic(music, 1);
	}
	// Login
	dataM = new DataManager("UI/background/login.bmp", "UI/background/menu.bmp", "UI/background/settings.bmp", nuevaPartida);
	isRunning = !dataM->Log();
	player.jugador = dataM->playerName();
	int mod = dataM->Modalidad();
	std::string labto = dataM->laberinto();
	switch(mod)
	{
	case 0:
		automatico = false;
		break;
	case 1:
		automatico = true;
		break;
	case 2:
		cpu = true;
	}


	std::string textura = dataM->textura();
	// Game
	argv[1] = labto.c_str();
	rMap = new ReadMap(argv);
	if(rMap->exist())
		map = new Map(rMap->getMap(), textura);
	else
		map = new Map();
	player.laberinto.push_back(rMap->labto());
	//fondo = new Object("images/piso2.bmp", 0, 0);
	jugarDenuevo = new Object("UI/retry.bmp", 0, 0);
	Ulose = new Object("UI/lose.bmp", 0, 0);
	Uwin = new Object("UI/win.bmp", 0, 0);
	Black = new Object("UI/black.bmp", 0, 0);
	if(nuevaPartida)
	{
		player.partidas++;
		nuevaPartida = false;
	}
}

void Game::events(){
	SDL_PollEvent(&Game::event);
	switch(Game::event.type){
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
		{
			switch(Game::event.button.button)
			{
			case SDL_BUTTON_LEFT:
				if((WIN || LOSE) && nuevo == 20)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					x -= map->getWidth()/2;
					y -= map->getHeight()/2;
					if(x < 322 && x > 260 &&
						y < 522 && y > 433)
					{
						isRunning = false;
						/* no repeticion */
						nuevaPartida = false;
					}
					else if(x < 505 && x > 444 &&
						y < 522 && y > 433)
					{
						isRunning = false;
						/* repeticion */
						nuevaPartida = true;
					}
				}
				if(!isRaton && (not automatico || cpu))
				{
					// validar que no haya un muro
					int x, y;
					SDL_GetMouseState(&x, &y);
					x -= map->getWidth()/2;
					y -= map->getHeight()/2;
					initX = x;
					initY = y;
					time(&now);
					Raton1.addComp<CoordComp>(initX, initY);
					Raton1.addComp<SpriteComp>("UI/personajes/raton/abajo1.bmp");
					Raton1.addComp<Keyboard>();
					if(!map->solveMap(initX, initY))
					{
						LOSE = true;
						isRaton = false;
					}
					else
						isRaton = true;
				}
				else if(!isRaton && automatico)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					x -= map->getWidth()/2;
					y -= map->getHeight()/2;
					initX = x;       	//coordenadas iniciales del raton
					initY = y;
					std::cout << "Buscando la ruta..." << std::endl;
					isRaton = map->solveMap(initX, initY);

					player.x.push_back(initX);
					player.y.push_back(initY);
					player.pasos.push_back(map->Ruta().size()/2);
					time(&now);

					if(!isRaton)
						std::cout << "No puede comenzar en un muro" << std::endl;
					else
					{
						Raton1.addComp<CoordComp>(initX, initY);
						Raton1.addComp<SpriteComp>("UI/personajes/raton/abajo1.bmp");
					}
					existeRuta = map->RutaEncontrada();
					if(!existeRuta)
					{
						std::cout << "Has perdido" << std::endl;
						LOSE = true;

					}
				}
				break;
			case SDL_BUTTON_RIGHT:
			if(cpu && isRaton){
					int x, y;
					SDL_GetMouseState(&x, &y);
					x -= map->getWidth()/2;
					y -= map->getHeight()/2;
					initX = x;       	//coordenadas iniciales del raton
					initY = y;
					std::cout << "Buscando la ruta..." << std::endl;
					isRaton = map->solveMap(initX, initY);
					if(!isRaton)
					{
						std::cout << "No puede comenzar en un muro" << std::endl;
						LOSE = true;
					}
					existeRuta = map->RutaEncontrada();
					if(!existeRuta)
					{
						std::cout << "Has perdido" << std::endl;
						LOSE = true;
					}
					automatico = true;
				}
			else if(isRaton && not automatico)
			{
				LOSE = true;
			}
				break;
				
			case SDL_BUTTON_X1:
				std::cout << "X1";
				break;
			}
			break;
		}
		default:
			break;
	}
}

void Game::update(){
	//Raton1.getComp<CoordComp>().position.Add(vec2D(3,0));//+vec2D(0,3));
	//std::cout << Raton1.getComp<CoordComp>().position.x << std::endl;
	if(isRaton && (not automatico || cpu))
	{
		double x, y;
		CoordComp* coord = &Raton1.getComp<CoordComp>();
		x = coord->scale;
		y = coord->scale;
		if(coord->position.x + x < 3)
			Raton1.getComp<CoordComp>().position.Add(vec2D(3,0));
		if(coord->position.y + y < 3)
			Raton1.getComp<CoordComp>().position.Add(vec2D(0,3));
		if(coord->position.x + x > 797)
			Raton1.getComp<CoordComp>().position.Sub(vec2D(3,0));
		if(coord->position.y + y > 697)
			Raton1.getComp<CoordComp>().position.Sub(vec2D(0,3));
	}

	manager.refresh();
	manager.update();
}

void Game::render(){
	SDL_RenderClear(renderer);                                                       
	//backround
	//fondo->render(false, false);
	if(!WIN && !LOSE){
		if (isRaton && not automatico)
		{
			// en manager
			double x, y;
			x = Raton1.getComp<CoordComp>().position.x;
			y = Raton1.getComp<CoordComp>().position.y;
			CoordComp* coord = &Raton1.getComp<CoordComp>();
			Keyboard* key = &Raton1.getComp<Keyboard>();
			bool choco = map->DrawMap(x+map->getWidth()/2, y+map->getHeight()/2, coord->scale);

			if(map->Ganaste())
				{
					WIN = true;
				}
			key->resetChoques();
			if(choco)
			{
				coord->velocity.invs();
				switch(key->direccion())
				{
				case 4:
					/*choque a Izquierda*/
					key->chocoLf();
					break;
				case 8:
					/*choque a Arriba*/
					key->chocoUp();
					break;
				case 6:
					/*choque a Derecha*/
					key->chocoRg();
					break;
				case 2:
					/*choque a Abajo*/
					key->chocoDw();
					break;
				}
				//coord->velocity.invs();
			}
			//Raton1.getComp<CoordComp>().position.x = newCoord.x;
			//Raton1.getComp<CoordComp>().position.y = newCoord.y;
		}
		else if (isRaton && automatico && existeRuta)
		{
			map->DrawSol();
			usleep(20000);
			if(!WIN && posX < map->getMap().size()*map->getMap()[0].size())
			{
				int ex = map->Ruta()[posX];
				int uai = map->Ruta()[posY];
				Raton1.getComp<CoordComp>().position.x = (ex-0.2)*map->getWidth();
				Raton1.getComp<CoordComp>().position.y = (uai-0.2)*map->getHeight();
				posX+=2;
				posY+=2;
				if(!WIN && map->getMap()[uai][ex]==2)
				{
					WIN = true;
					std::cout << "Ganaste" << std::endl;

				}
			}
		}
		else
			map->DrawMap();
		
		manager.draw(); //players
	}
	else
	{	

		if(nuevo < 10 &&  LOSE)
		{
			Ulose->render(false, false);
			time(&after);
			TTF_Font *Font = TTF_OpenFont( "UI/ttf/slkscrb.ttf", 28 );
			SDL_Color logColor = {128, 128, 128, 128};
			std::string tempito = "Tiempo: "+std::to_string(after-now);

			texto textComponents = TextureManager::loadFromRenderedText(tempito.c_str(), logColor, Font);
			SDL_Rect logDest = { 40,450, textComponents.width, textComponents.height };
			SDL_Texture* logTexture = textComponents.texture;
			TextureManager::DrawDest(logTexture, logDest);
			nuevo++;
		}
		else if(nuevo < 10 && WIN)
		{
			Uwin->render(false, false);
			time(&after);
			TTF_Font *Font = TTF_OpenFont( "UI/ttf/slkscrb.ttf", 28 );
			SDL_Color logColor = {128, 128, 128, 128};
			std::string tempito = "Tiempo: "+std::to_string(after-now);

			texto textComponents = TextureManager::loadFromRenderedText(tempito.c_str(), logColor, Font);
			SDL_Rect logDest = { 40, 450, textComponents.width, textComponents.height };
			SDL_Texture* logTexture = textComponents.texture;
			TextureManager::DrawDest(logTexture, logDest);
			nuevo++;
		}
		
		if(nuevo==10)
		{
			nuevo++;
			if(automatico)
			{
				dataM->agregarPartida(player);
			}
		}
		if(nuevo == 11)
		{
			nuevo++;
			sleep(2);
		}
		if(nuevo>11 && nuevo < 20)
		{
			Black->render(false, false);
			TTF_Font *Font = TTF_OpenFont( "UI/ttf/Lato-Light.ttf", 30 );
			TTF_Font *font = TTF_OpenFont( "UI/ttf/slkscr.ttf", 30 );
			SDL_Color logColor = {128, 128, 128, 128};
			std::string tempito = "Jugador   x   y   pasos   laberintos";
			std::ifstream file;
			/*
			SDL_Rect d1,d2,d3,d4,d5,d6,d7,d8,d9,d10;
			SDL_Texture* T1;
			SDL_Texture* T2;
			SDL_Texture* T3;
			SDL_Texture* T4;
			SDL_Texture* T5;
			SDL_Texture* T6;
			SDL_Texture* T7;
			SDL_Texture* T8;
			SDL_Texture* T9;
			SDL_Texture* T10;
			*/
			texto textComponents = TextureManager::loadFromRenderedText(tempito.c_str(), logColor, font);
			SDL_Rect logDest = { 50, 20, textComponents.width, textComponents.height };
			SDL_Texture* logTexture = textComponents.texture;
			TextureManager::DrawDest(logTexture, logDest);
			std::string out;
			std::vector<std::string> vec;

			file.open("datos/partidas.txt");
			if (file.is_open())
			{
				int i = 0;
				while( i < 10 && !file.eof())
				{
					getline(file,out);
					vec.push_back(out);
				}
					if(1 <= vec.size())
					{
					std::string t1 = "1-     "+vec[0];
					texto c1 = TextureManager::loadFromRenderedText(t1.c_str(), logColor, Font);
					SDL_Rect d1 = { 15, 50+10, c1.width, c1.height };
					SDL_Texture* T1 = c1.texture;
					TextureManager::DrawDest(T1, d1);
					}
					if(2 <= vec.size())
					{
					std::string t2 = "2-     "+vec[1];
					texto c2 = TextureManager::loadFromRenderedText(t2.c_str(), logColor, Font);
					SDL_Rect d2 = { 15, 100+10, c2.width, c2.height };
					SDL_Texture* T2 = c2.texture;
					TextureManager::DrawDest(T2, d2);
					}
					if(3 <= vec.size())
					{
					std::string t3 = "3-     "+vec[2];
					texto c3 = TextureManager::loadFromRenderedText(t3.c_str(), logColor, Font);
					SDL_Rect d3 = { 15, 150+10, c3.width, c3.height };
					SDL_Texture* T3 = c3.texture;
					TextureManager::DrawDest(T3, d3);
					}
					if(4 <= vec.size())
					{
					std::string t4 = "4-     "+vec[3];
					texto c4 = TextureManager::loadFromRenderedText(t4.c_str(), logColor, Font);
					SDL_Rect d4 = { 15, 200+10, c4.width, c4.height };
					SDL_Texture* T4 = c4.texture;
					TextureManager::DrawDest(T4, d4);
					}
					if(5 <= vec.size())
					{
					std::string t5 = "5-     "+vec[4];
					texto c5 = TextureManager::loadFromRenderedText(t5.c_str(), logColor, Font);
					SDL_Rect d5 = { 15, 250+10, c5.width, c5.height };
					SDL_Texture* T5 = c5.texture;
					TextureManager::DrawDest(T5, d5);
					}
					if(6 <= vec.size())
					{
					std::string t6 = "6-     "+vec[5];
					texto c6 = TextureManager::loadFromRenderedText(t6.c_str(), logColor, Font);
					SDL_Rect d6 = { 15, 300+10, c6.width, c6.height };
					SDL_Texture* T6 = c6.texture;
					TextureManager::DrawDest(T6, d6);
					}
					if(7 <= vec.size())
					{
					std::string t7 = "7-     "+vec[6];
					texto c7 = TextureManager::loadFromRenderedText(t7.c_str(), logColor, Font);
					SDL_Rect d7 = { 15, 350+10, c7.width, c7.height };
					SDL_Texture* T7 = c7.texture;
					TextureManager::DrawDest(T7, d7);
					}
					if(8 <= vec.size())
					{
					std::string t8 = "8-     "+vec[7];
					texto c8 = TextureManager::loadFromRenderedText(t8.c_str(), logColor, Font);
					SDL_Rect d8 = { 15, 400+10, c8.width, c8.height };
					SDL_Texture* T8 = c8.texture;
					TextureManager::DrawDest(T8, d8);
					}
					if(9 <= vec.size())
					{
					std::string t9 = "9-     "+vec[8];
					texto c9 = TextureManager::loadFromRenderedText(t9.c_str(), logColor, Font);
					SDL_Rect d9 = { 15, 450+10, c9.width, c9.height };
					SDL_Texture* T9 = c9.texture;
					TextureManager::DrawDest(T9, d9);
					}
					if(10 <= vec.size())
					{
					
					std::string t10 = "10-     "+vec[9];
					texto c10 = TextureManager::loadFromRenderedText(t10.c_str(), logColor, Font);
					SDL_Rect d10 = { 15, 500+10, c10.width, c10.height };
					SDL_Texture* T10 = c10.texture;
					TextureManager::DrawDest(T10, d10);
					}
					
			}

			nuevo++;
		}

		if(nuevo == 18)
		{
			sleep(5);
		}

		if(nuevo==20 && (WIN || LOSE))
			jugarDenuevo->render(false, false);
	}
	SDL_RenderPresent(renderer);
}

void Game::clean(){
	Mix_FreeMusic( music );
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}


//--------------------------------------------------------------------------------------------

Object::Object(const char* texture, int x, int y){
	objTex = TextureManager::LoadTexture(texture);
	this->x = x;
	this->y = y;
}

void Object::update(positions x){ // moverse
	this->x += x.X;
	this->y += x.Y;

	this->sourceR.h = x.h1;
	this->sourceR.w = x.w1;
	this->sourceR.x = x.x1;
	this->sourceR.y = x.x2;

	this->destinationR.w = x.w2;
	this->destinationR.h = x.h2;
	this->destinationR.x = this->x*5; //speed
	this->destinationR.y = this->y*5;
}

void Object::render(bool sr, bool dr){
	if (sr && dr)
		TextureManager::Draw(this->objTex, this->sourceR, this->destinationR);
	else if (!sr && dr)
		TextureManager::DrawDest(this->objTex, this->destinationR);
	else if (sr && !dr)
		TextureManager::DrawSrc(this->objTex, this->sourceR);
	else if(!(sr || dr))
		TextureManager::DrawNull(this->objTex);
}

//--------------------------------------------------------------------------------------------

texto TextureManager::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* font )
{
	texto x;
	SDL_Texture* mTexture;
	if( mTexture != NULL )
    {
      	SDL_DestroyTexture( mTexture );
     	mTexture = NULL;
    }
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if(!textSurface)
		std::cout << "textSurface not created" << std::endl;
	else
	{
		mTexture = SDL_CreateTextureFromSurface( Game::renderer, textSurface );
		if(!mTexture)
			std::cout << "mTexture not created" << std::endl;
		else
		{
			x.width = textSurface->w;
			x.height = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	x.texture = mTexture;
	return x;
}