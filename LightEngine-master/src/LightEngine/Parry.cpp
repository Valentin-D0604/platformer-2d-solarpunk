#include "Parry.h"
#include "RectangleCollider.h"

Parry::Parry(sf::Vector2f pos, sf::Vector2f size) {
	m_collider = new RectangleCollider(pos, size);
}