#include "Entity.h"

#include "../Managers/GameManager.h"

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}

template<typename T>
inline T* Entity::CreateEntity()
{
	return GetScene()->CreateEntity<T>();
}
