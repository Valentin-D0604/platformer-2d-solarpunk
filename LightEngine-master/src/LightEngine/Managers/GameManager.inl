#pragma once

#include "GameManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Scene/Scene.h"

template<typename T>
void GameManager::LaunchScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	_ASSERT(mpScene == nullptr);

	T* newScene = new T();
	mpScene = newScene;

	mpScene->SetGameManager(this);

	mpScene->createView();
	mpScene->m_view->setSize(sf::Vector2f(mWindowWidth, mWindowHeight));
	mpScene->m_view->setCenter(sf::Vector2f(mWindowWidth/2, mWindowHeight/2));
	mpWindow->setView(*(mpScene->m_view));

	mpScene->OnInitialize();

	Run();
}
