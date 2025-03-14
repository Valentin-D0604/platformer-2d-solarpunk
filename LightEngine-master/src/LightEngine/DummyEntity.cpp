#include "DummyEntity.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Debug.h"
#include "Managers.h"
#include "Sprite.h"
#include <iostream>

void DummyEntity::OnInitialize() {
	m_sprite = new Sprite();

	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));

	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);
	m_collider->setGizmo(true);
}

void DummyEntity::onCollision(Entity* other)
{
	//	std::cout << "dummy colide";
		Debug::DrawText(GetPosition().x, GetPosition().y - 225, "life", 0.5f, 0.5f, sf::Color::Red);
		Destroy();
}