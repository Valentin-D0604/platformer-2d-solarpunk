#pragma once
#include "Entity.h"
class Background : public Entity
{
	Entity* m_player;
	sf::Vector2f m_basePos;

	void OnInitialize();
	void OnUpdate();
public:
	void SetPlayer(Entity* _player);
};

