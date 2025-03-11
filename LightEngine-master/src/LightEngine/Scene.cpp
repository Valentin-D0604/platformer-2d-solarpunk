#include "Scene.h"

#include "Managers/GameManager.h"

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

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}
