#include "DummyEntity.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include <iostream>

void DummyEntity::OnInitialize() {
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);
}

void DummyEntity::onCollision(Entity* other)
{
		std::cout << "dummy colide";

}