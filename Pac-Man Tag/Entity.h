/*
Created by Paul O'Callghan
Enity will hold all things entity related, not to be confused with GameObject. Enitity can be used for when you wish to attach specific things
to it and not require an update or fixed update every frame
*/

#pragma once
#include <queue>
#include <string>
#include "I_ComponentSystem.h"


class Entity
{
public:
	Entity();
	Entity(std::string name);
	~Entity();

	int getId();
	std::string getName();
	void setName(std::string name);

	static void clearReusableIds();

	template<class T>
	inline void addComponent(T& t);
	template<class T>
	inline void removeComponent(T t);
	template<class T>
	inline void destroyComponent(T t);
	template<class T>
	inline bool hasComponent(T t);

private:
	static int currentAssignableId;
	static std::queue<int> reusableIds;

	int id;
	std::string name;
};


	// Adds a blank component of type T
template<class T>
inline void Entity::addComponent(T& t)
{
	if (std::is_base_of<Component, T>())
	{
		I_ComponentSystem<T>::addComponent(id, t);
	}
}

template<class T>
inline void Entity::removeComponent(T t)
{
	if (std::is_base_of<Component, T>())
	{
		I_ComponentSystem<T>::removeComponent(id);
	}
}

template<class T>
inline void Entity::destroyComponent(T t)
{
	if (std::is_base_of<Component, T>())
	{
		I_ComponentSystem<T>::destroyComponent(id);
	}
}

template<class T>
inline bool Entity::hasComponent(T t)
{
	if (std::is_base_of<Component, T>())
	{
		return I_ComponentSystem<T>::hasComponent(id);
	}
	return false;
}
	