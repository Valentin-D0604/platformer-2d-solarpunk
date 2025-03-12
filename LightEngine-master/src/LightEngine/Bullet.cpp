#include "Bullet.h"
#include "RectangleCollider.h"
#include "TestScene.h"

#include <iostream>

void Bullet::InitBullet(sf::Vector2f position, sf::Vector2f direction, bool state) {
	std::cout << "m_lastDir: " << direction.x << ", " << direction.y << std::endl;
	m_pos = position;
	m_dir = direction;
	m_onTheGround = state;
	SetPosition(position.x, position.y);
}

void Bullet::OnInitialize() {
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);
	SetTag(TestScene::Tag::bullet);
}

void Bullet::OnUpdate() {
	if (!m_onTheGround) {
		SetDirection(m_dir.x, m_dir.y, 200);
	}
	else if (m_onTheGround) {
		setMass(20);
	}
}

void Bullet::onCollision(Entity* other) {

}

bool Bullet::IsBulletOnGround() {
	return m_onTheGround;
}