#include "DummyEntity.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include <iostream>

void DummyEntity::OnInitialize() {
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);
}

void DummyEntity::OnCollision(Entity* other)
{
	Collider* coll = dynamic_cast<Collider*>(other);
	if (m_collider->isColliding(coll)) {
		std::cout << "dummy colide";
	}
}