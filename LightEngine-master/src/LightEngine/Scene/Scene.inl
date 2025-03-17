	#pragma once

#include "Scene.h"
#include "../Managers/GameManager.h"
#include "../Entity/Entity.h"


template<typename T>
inline T* Scene::CreateEntity()
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->Initialize();

	mp_GameManager->m_entitiesToAdd.push_back(newEntity);

	return newEntity;
}
