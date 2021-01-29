/*
	Created by Paul O'Callaghan
	This Interface contains some generic implementations where as the rest of it must be implemented by yourself the user.
*/


#pragma once
#include "Component.h"
#include <map>
#include <queue>
#include <vector>


template<class T>
class I_ComponentSystem
{
public:
	I_ComponentSystem() {};
	virtual inline ~I_ComponentSystem() = 0;

	// Generic Implementations
	static void addComponent(int entityId);

	// Adds a blank component of type T
	static void addComponent(int entityId, T t);

	// Removes component from entity and places it in a recyclable pool
	static void removeComponent(int entityId);
	static void removeComponents(int entityId);

	// Destroys / Deletes component from memeory
	static void destroyComponent(int entityId);
	static void destroyComponents(int entityId);

	static bool hasComponent(int entityId);

	// Returns first element null/blank if empty
	static T& getComponent(int entityId);

	// Returns list of components type T attached to entity
	static std::vector<T>& getComponents(int entityId);

	static int getRecycablePoolSize();

	static std::map<int, std::vector<T>>& getEntities();
	static std::queue<T>& getRecycalblePool();

	// Required to be implemented by the user
	virtual void update() = 0;


protected:
	static std::map<int, std::vector<T>> entities;

	static std::queue<T> recycablePool;
	
};

template<class T>
I_ComponentSystem<T>::~I_ComponentSystem() {}


template<class T>
std::map<int, std::vector<T>> I_ComponentSystem<T>::entities = { {} };

template<class T>
std::queue<T> I_ComponentSystem<T>::recycablePool = {};


template<class T>
inline void I_ComponentSystem<T>::addComponent(int entityId)
{
	if (recycablePool.empty() == false)
	{
		entities[entityId].push_back(recycablePool.front());
		recycablePool.pop();
		return;
	}
	T newClassComponent;

	entities[entityId].push_back(newClassComponent);
}

template<class T>
inline void I_ComponentSystem<T>::addComponent(int entityId, T newComponent)
{
	 entities[entityId].push_back(newComponent);
}

// Removes first component if there is more than 1
template<class T>
inline void I_ComponentSystem<T>::removeComponent(int entityId)
{
	if (!hasComponent(entityId))
	{
		return;
	}

	typename std::map<int, std::vector<T> >::iterator it = entities.find(entityId);
	recycablePool.push(it->second.at(0));
	it->second.erase(it->second.begin());

	if (it->second.size() == 0)
	{
		entities.erase(entityId);
	}
}

template<class T>
inline void I_ComponentSystem<T>::removeComponents(int entityId)
{
	if (!hasComponent(entityId))
	{
		return;
	}

	typename std::map<int, std::vector<T> >::iterator it = entities.find(entityId);

	while (it->second.size() > 0)
	{
		recycablePool.push(it->second.at(0));
		it->second.erase(it->second.begin());
	}

	if (it->second.size() == 0)
	{
		entities.erase(entityId);
	}
}

// Removes first element found with component without assigning it to a pool
template<class T>
inline void I_ComponentSystem<T>::destroyComponent(int entityId)
{
	if (!hasComponent(entityId))
	{
		return;
	}

	typename std::map<int, std::vector<T> >::iterator it = entities.find(entityId);
	it->second.erase(it->second.begin());

	
	if (it->second.size() == 0)
	{
		entities.erase(entityId);
	}
}

// Reoves all components and removes entity from map without assigning objects to a pool 
template<class T>
inline void I_ComponentSystem<T>::destroyComponents(int entityId)
{
	if (!hasComponent(entityId))
	{
		return;
	}

	entities.erase(entityId);
}

template<class T>
inline bool I_ComponentSystem<T>::hasComponent(int entityId)
{
	typename std::map<int, std::vector<T> >::iterator it = entities.find(entityId);

	if (it == entities.end())
	{
		return false;
	}
	return true;
}

template<class T>
inline T& I_ComponentSystem<T>::getComponent(int entityId)
{
	if (!hasComponent(entityId))
	{
		addComponent(entityId);
	}

	typename std::map<int, std::vector<T> >::iterator it = entities.find(entityId);
	return it->second.at(0);
}

template<class T>
inline std::vector<T>& I_ComponentSystem<T>::getComponents(int entityId)
{
	if (!hasComponent(entityId))
	{
		addComponent(entityId);
	}

	typename std::map<int, std::vector<T> >::iterator it = entities.find(entityId);
	return it->second;
}

template<class T>
inline int I_ComponentSystem<T>::getRecycablePoolSize()
{
	return getRecycalblePool().size();
}

template<class T>
inline std::map<int, std::vector<T>>& I_ComponentSystem<T>::getEntities()
{
	return entities;
}

template<class T>
inline std::queue<T>& I_ComponentSystem<T>::getRecycalblePool()
{
	return recycablePool;
}
