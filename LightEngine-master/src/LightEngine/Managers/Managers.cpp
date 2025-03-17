#include "Managers.h"

#include "../Managers/GameManager.h"
#include "../Managers/ResourceManager.h"

Managers* Managers::m_Instance = nullptr;

Managers::Managers()
{
	m_Instance = this;

	m_ResourceManager = new ResourceManager();
	m_GameManager = new GameManager();
}

void Managers::run()
{
	m_GameManager->Run();
}
