#include "Scene.h"

#include "../Managers/GameManager.h"

#define SCREEN_SIZE_X
#define SCREEN_SIZE_Y

int Scene::GetWindowWidth() const
{
	return mp_GameManager->m_windowWidth;
}

int Scene::GetWindowHeight() const
{
	return mp_GameManager->m_windowHeight;
}

void Scene::SetCameraCenter(sf::Vector2f _position)
{
	m_view->setCenter(_position);
}

void Scene::SetCameraZoom(float _zoom)
{
	m_view->setSize(GetWindowWidth() * _zoom, GetWindowHeight() * _zoom);
}

float Scene::GetDeltaTime() const
{
	return mp_GameManager->m_deltaTime;
}
