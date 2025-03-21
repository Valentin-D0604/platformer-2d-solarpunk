#include "DummyEntity.h"
#include "../Collision/CircleCollider.h"
#include "../Collision/RectangleCollider.h"
#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include "../Graphics/Sprite.h"
#include <iostream>

void DummyEntity::OnInitialize() {
	m_sprite = new Sprite();

	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("test")));

	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);

}

void DummyEntity::OnCollision(Entity* other)
{
	//	std::cout << "dummy colide";
		Debug::DrawText(GetPosition().x, GetPosition().y - 225, "life", 0.5f, 0.5f, sf::Color::Red);
		Destroy();
}