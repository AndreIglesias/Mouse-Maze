#pragma once
#include "Game.hpp"

// Lista lineal
//----------------------------------------------------------------------
template <class T>          //  Input into function with any type
T input(std::istream& stream){
  T i;
  stream >> i;
  return i;
}

inline int pModulo(int i, int n) {return (i % n + n) % n;}

///---------------------------------------------------------------------
//! Attributes of the AUX class
#define Attributes \
  X(long int, x)				\
  X(long int, y)				\
  X(long int, pasos)			\
  X(std::string, jugador)		\
  X(std::string, laberinto)
  
class AUX{
private:
	std::ofstream escribir;
#define X(type, name) type name;
  Attributes
#undef X
  public:
  AUX(){}
  AUX(Jugador j){
	escribir.open("datos/.partidas.txt");
#define X(type, name) \
	set##name(j.name[j.partidas]);
	Attributes
#undef X
}
  
  // GET & SET METHODS
#define X(type, name) void set##name(type param){name = param;};type get##name(){return name;}
  Attributes
#undef X
  
  // SHOW ALL ELEMENTS
  //Estructura a escribir $x$y$pasos$jugador$laberinto
  void show(){
#define X(type, name) escribir<<"$"<<get##name();
    Attributes
#undef X
    escribir<<std::endl;
      }
};

typedef struct n{
	AUX* A;
	struct n* nxt=NULL; 
	n(Jugador j){A = new AUX(j);}
	n(){}
}node;
//--------------------------------------------------------------------

class List
{
private:
	node* start = new node;
	int size = 0;
public:
	List();
	void append(node*);
	node* createAuxNode(Jugador);
	void print();
	void deleteNode(node*);
	void deleteList();

};
List::List(){ start = NULL; }

node* List::createAuxNode(Jugador j)
{
  node* NEW = new node(j);
  size++;
  return NEW;
}

void List::deleteNode(node* p){
  if(p==start) start=p->nxt;
  else if(start){ // tie up the other nodes
    node* q=start;
    while(q && q->nxt)
    {
      if(q->nxt==p)
      {
		q->nxt=q->nxt->nxt;
      }
      q=q->nxt;
    }
  }
  // delete node
  delete p;
  p = NULL;
}

void List::deleteList(){
  node* p=start;
  if(p){
    do{ deleteNode(p);p=p->nxt; }while(p);
    start=NULL;
  }
}

void List::append(node* NEW){ //Inserting node at the end of the list
	std::cout << "the best";
  if(!start)
  	{NEW->nxt=start;start=NEW;}
  else{
    node* p=start;

    while(p->nxt) 
    	p=p->nxt;

    p->nxt=NEW;
    NEW->nxt=NULL;
  }
}

void List::print(){
  node* p=start;
  while(p)
  	{ p->A->show();p=p->nxt; }
}