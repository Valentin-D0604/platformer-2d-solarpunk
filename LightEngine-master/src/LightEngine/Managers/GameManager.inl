#pragma once

#include "GameManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Scene/Scene.h"

template<typename T>
void GameManager::LaunchScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	_ASSERT(mp_Scene == nullptr);

	T* newScene = new T();
	mp_Scene = newScene;

	mp_Scene->SetGameManager(this);

	mp_Scene->CreateView();
	mp_Scene->m_view->setSize(sf::Vector2f(m_windowWidth, m_windowHeight));
	mp_Scene->m_view->setCenter(sf::Vector2f(m_windowWidth/2, m_windowHeight/2));
	mp_Window->setView(*(mp_Scene->m_view));

	mp_Scene->OnInitialize();

	Run();
}
