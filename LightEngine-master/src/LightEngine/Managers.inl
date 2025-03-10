#include "Managers/GameManager.h"
#include "Managers/ResourceManager.h"

template<typename T>
inline T* Managers::get()
{
	if (std::is_same<GameManager, T>::value) {
		return (T*)m_instance->m_gameManager;
	}
	else if (std::is_same<ResourceManager, T>::value) {
		return(T*)m_instance->m_resourceManager;
	}

	return nullptr;
}
