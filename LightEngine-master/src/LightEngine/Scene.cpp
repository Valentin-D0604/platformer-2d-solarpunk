#include "Scene.h"

#include "Managers/GameManager.h"

#define SCREEN_SIZE_X
#define SCREEN_SIZE_Y

int Scene::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

void Scene::setCameraCenter(sf::Vector2f _position)
{
	m_view->setCenter(_position);
}

void Scene::setCameraZoom(float _zoom)
{
	m_view->setSize(GetWindowWidth() * _zoom, GetWindowHeight() * _zoom);
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}
