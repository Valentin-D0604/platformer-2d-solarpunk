#include "DummyEntity.h"
#include "../Collision/CircleCollider.h"
#include "../Collision/RectangleCollider.h"
#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include "../Graphics/Sprite.h"
#include <iostream>

void DummyEntity::OnInitialize() {
	m_Sprite = new Sprite();

	m_Sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));

	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_Collider = new RectangleCollider(pos, size);
	m_Collider->setGizmo(true);
}

void DummyEntity::onCollision(Entity* other)
{
	//	std::cout << "dummy colide";
		Debug::DrawText(GetPosition().x, GetPosition().y - 225, "life", 0.5f, 0.5f, sf::Color::Red);
		Destroy();
}