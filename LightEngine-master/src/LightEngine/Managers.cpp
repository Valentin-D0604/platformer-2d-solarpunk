#include "Managers.h"

#include "Managers/GameManager.h"
#include "Managers/ResourceManager.h"

Managers* Managers::m_instance = nullptr;

Managers::Managers()
{
	m_instance = this;

	m_resourceManager = new ResourceManager();
	m_gameManager = new GameManager();
}

void Managers::run()
{
	m_gameManager->Run();
}
