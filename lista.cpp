#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

typedef struct j
{
  long long int x, y, pasos;
  std::string jugador, laberinto;
}Jugador;

struct nodo
{
  Jugador player;
  struct nodo* sig;
};

class Lista
{
private:
  nodo* inicio = new nodo;
  std::ofstream escribir;
  std::ifstream leer;
public:
  Lista() { inicio = NULL; escribir.open("datos/AuxPartidas.txt"); leer.open("datos/partidas.txt");}
  ~Lista() {}
  nodo* initio() { return inicio; }
  void print()
  {
    nodo* p=inicio;
    while(p) // jugador$x$y$pasos$laberinto
      {
        escribir << p->player.jugador << " ";
        escribir << p->player.x << " ";
        escribir << p->player.y << " ";
        escribir << p->player.pasos << " ";
        escribir << p->player.laberinto << std::endl;
        p=p->sig;
      }
  }
  void insert(Jugador player)
  {
    nodo* nuevo = new nodo;
    nuevo->player = player;
    nuevo->sig = inicio;
    inicio = nuevo;
  }
  void deleteList()
  {
    nodo* p = inicio;
    nodo* aux;
    while(p)
    { 
      aux = p->sig;
      delete p;
      p = aux;
    }
    delete aux;
  }
  void read()
  {
    std::string out, aux = "";
    int cont;
    const char* value;
    Jugador p;
    std::stringstream strValue;
    std::string str;
    if (leer.is_open())
    {
      while (leer >> p.jugador >> p.x >> p.y >> p.pasos >> p.laberinto)
      {
        //std::cout << p.jugador << p.x << p.y << p.pasos << p.laberinto << std::endl;
        insert(p);
      }
    }  
  }
};




  nodo* sortedMerge(nodo* a, nodo* b);
  void frontBackSplit(nodo* source, nodo** frontRef, nodo** backRef);

  void mergeSort(nodo** inicio)
  {
    nodo* head = *inicio;
    nodo* a;
    nodo* b;

    if( ( head == NULL || head->sig == NULL ) )
      return;
    frontBackSplit(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *inicio = sortedMerge(a, b);
  }

  nodo* sortedMerge(nodo* a, nodo* b)
  {
    nodo* result = NULL;
    if(a==NULL)
      return b;
    else if(b==NULL)
      return a;
    if(a->player.pasos <= b->player.pasos)
    {
      result = a;
      result->sig = sortedMerge(a->sig, b);
    }
    else
    {
      result = b;
      result->sig = sortedMerge(a, b->sig);
    }
    return result;
  }

void frontBackSplit(nodo* source, nodo** frontRef, nodo** backRef)
{
  nodo* fast;
  nodo* slow;
  if(source==NULL || source->sig==NULL)
  {
    *frontRef =source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->sig;
    while(fast!=NULL)
    {
      fast = fast->sig;
      if(fast!=NULL)
      {
        slow = slow->sig;
        fast = fast->sig;
      }
    }
    *frontRef = source;
    *backRef = slow->sig;
    slow->sig = NULL;
  }
}

int main(int argc, char const *argv[])
{
  /* code */
  int aux;
  const char* value;
  std::stringstream strValue;
  Lista lst;
  Jugador p;


  p.jugador = argv[1];
  p.laberinto = argv[5];
  
  p.x = atoi(argv[2]);

  p.y = atoi(argv[3]);
  
  p.pasos = atoi(argv[4]);

  lst.read();
  lst.insert(p);
  nodo* inicio = lst.initio();
  mergeSort(&inicio);
  lst.print();
  remove("datos/partidas.txt");
  rename("datos/AuxPartidas.txt", "datos/partidas.txt");
  //lst.topTen();
  lst.deleteList();

  return 0;
}