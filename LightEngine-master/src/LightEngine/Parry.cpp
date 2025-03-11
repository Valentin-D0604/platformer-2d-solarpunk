#include "Parry.h"
#include "DummyEntity.h"
#include "RectangleCollider.h"
#include <iostream>

void Parry::onCollision(Entity* other)
{
	if (!other->IsTag(mTag)) {
		std::cout << "Parry colide";
	}
}

void Parry::OnInitialize() {
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);
	std::cout << "created";
	SetTag(1);
}

void Parry::OnUpdate() {
	m_parryTime += GetDeltaTime();
	if (m_parryTime >= 0.5) {
		//Destroy();
		//delete m_collider;
		//m_collider = nullptr;
		return;
	}
}