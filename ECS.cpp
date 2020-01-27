#include "ECS.hpp"

//-----------------------------------------ENTITY----------------------------------------
Entity::Entity(){}
Entity::~Entity(){}

void Entity::update()
{
	for(auto& c : comps)c->update(); // Actualiza las posiciones de los componentes
}

void Entity::draw()
{
	for(auto& c : comps)c->draw();		//Dibuja los componentes donde deberian estar
}

//-----------------------------------------MANAGER----------------------------------------
void Manager::refresh()
{
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),[](const std::unique_ptr< Entity > &entity)
			{return !entity->isActive();}), std::end(entities));
}

Entity& Manager::addEntity()
{
	Entity* e = new Entity();
	std::unique_ptr < Entity > uniqueP{e};
	entities.emplace_back(std::move(uniqueP));
	return *e;
}