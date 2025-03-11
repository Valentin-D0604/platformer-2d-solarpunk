#include "Parry.h"
#include "RectangleCollider.h"

Parry::Parry(sf::Vector2f pos, sf::Vector2f size) {
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);
}