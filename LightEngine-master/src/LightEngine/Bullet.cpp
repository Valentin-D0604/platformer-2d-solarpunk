#include "Bullet.h"
#include "RectangleCollider.h"
#include "TestScene.h"
#include "Player.h"
#include "Mob1.h"

#include <iostream>

void Bullet::InitBullet(sf::Vector2f position, sf::Vector2f direction,Entity* caster, bool state) {
	std::cout << "m_lastDir: " << direction.x << ", " << direction.y << std::endl;
	m_caster = caster;
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
	if (other->IsTag(TestScene::Tag::mob1)) {
		Mob1* enemy = dynamic_cast<Mob1*>(other);
		enemy->TakeDamage(1);
	}
	if (other->IsTag(TestScene::Tag::player)) {
		Player* player = dynamic_cast<Player*>(other);
		if (IsBulletOnGround()) player->AddBullet(1);
		else if (other != m_caster && !IsBulletOnGround()) player->TakeDamage(1);
	}
	if(other != m_caster)Destroy();
}

bool Bullet::IsBulletOnGround() {
	return m_onTheGround;
}