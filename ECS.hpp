#pragma once
//entity component system

#include <algorithm>
#include <vector>
#include <bitset>
#include <array>
#include <memory>
#include <iostream>
#include "Game.hpp"


using CompID = std::size_t;
class Component;
class Entity;

// ------------------------------------------------------------

inline CompID getCompID()
{
	static CompID lastID = 0;
	return lastID++;
}

template <typename T>
inline CompID getCompID() noexcept
{
	static CompID typeID = getCompID();
	return typeID;
}

constexpr std::size_t maxComp = 32;

using CompBitSet = std:: bitset<maxComp>;
using CompArray = std::array<Component*, maxComp>;

// -----------------------------------------------------------

//game.getcomps<posComp>().setX(464564)
class Entity
{
public:
	Entity();
	~Entity();
	void update();								//actualiza los datos y valores de la entidad
	void draw();								//dibuja la entidad
	bool isActive() const { return active; }	//retorna si esta activa la entidad
	void destroy() { active = false; }			//Se vuelve inactiva la entidad


	template <typename T>
	bool hasComp() const;						//verifica si tiene componentes

	template <typename T, typename... args>
	T& addComp(args&&... arg);					//agrega componentes

	template<typename T>
	T& getComp() const;							//devuelve componentes


private:
	bool active = true;
	std::vector < std::unique_ptr <Component> > comps;

	CompArray compA;
	CompBitSet compB;
	
};

class Component
{
public:
	Entity* entity;

	virtual void init(){}
	virtual void update(){}
	virtual void draw(){}

	virtual ~Component(){}
	
};

class Manager
{
public:
	void update(){ for(auto& e : entities) e->update(); } 	// actualiza cada entidad

	void draw(){ for(auto& e : entities) e->draw(); } 		//dibuja cada entidad

	void refresh();

	Entity& addEntity();

private:
	std::vector< std::unique_ptr <Entity> > entities;
	
};

//----------------------------------------------------------------------------------------
/*
Templates functions, including member functions, 
must be written entirely in headers. This means 
that if you have a template class, its implementation
must be entirely in a header. This is because 
the compiler needs to have access to the entire
template definition (not just the signature) 
in order to generate code for each instantiation 
of the template.
*/

template <typename T>
bool Entity::hasComp() const {	return compB[getCompID<T>];	}

template < typename T, typename... args >
T& Entity::addComp(args&&... arg)
{
	T* c = new T(std::forward<args>(arg)...);
	c->entity = this;
	std::unique_ptr < Component > uniqueP { c };
	comps.emplace_back(std::move(uniqueP));

	compA[getCompID<T>()] = c;
	compB[getCompID<T>()] = true;

	c->init();
	return *c;
}

template<typename T>
T& Entity::getComp() const
{
	auto ptr = compA[getCompID<T>()];
	return *static_cast<T*>(ptr);
}
