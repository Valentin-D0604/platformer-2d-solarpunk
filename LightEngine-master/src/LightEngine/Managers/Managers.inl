#include "GameManager.h"
#include "ResourceManager.h"

template<typename T>
inline T* Managers::get()
{
	if (std::is_same<GameManager, T>::value) {
		return (T*)m_Instance->m_GameManager;
	}
	else if (std::is_same<ResourceManager, T>::value) {
		return(T*)m_Instance->m_ResourceManager;
	}

	return nullptr;
}
