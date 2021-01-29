#include "Entity.h"
#include  <iostream>
#include <type_traits>

Entity::Entity()
{
	name = " ";
	if (reusableIds.size() == 0)
	{
		id = currentAssignableId++;
		return;
	}
	id = reusableIds.front();
	reusableIds.pop();

}

Entity::Entity(std::string name)
{
	this->name = name;
	if (reusableIds.size() == 0)
	{
		id = currentAssignableId++;
		return;
	}
	id = reusableIds.front();
	reusableIds.pop();
}

Entity::~Entity()
{
	/*reusableIds.push(id);*/
}
int Entity::getId()
{
	return id;
}

std::string Entity::getName()
{
	return name;
}

void Entity::setName(std::string name)
{
	this->name = name;
}
void Entity::clearReusableIds()
{
	while (!reusableIds.empty())
	{
		reusableIds.pop();
	}
}

// static intitialisers
int Entity::currentAssignableId = 0;
std::queue<int> Entity::reusableIds = std::queue<int>();