#include "Bullet.h"
#include "../Collision/RectangleCollider.h"
#include "../Scene/TestScene.h"
#include "Player.h"
#include "Mob1.h"
#include "../Graphics/Sprite.h"
#include "../Managers/Managers.h"

#include <iostream>

void Bullet::InitBullet(sf::Vector2f position, sf::Vector2f direction,Entity* caster, bool state) {
	std::cout << "m_lastDir: " << direction.x << ", " << direction.y << std::endl;
	m_Caster = caster;
	m_Pos = position;
	m_Dir = direction;
	m_OnTheGround = state;
	SetPosition(position.x, position.y);
}

void Bullet::OnInitialize() {
	m_Sprite = new Sprite();
	m_Sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));

	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_Collider = new RectangleCollider(pos, size);
	SetTag(TestScene::Tag::bullet);
}

void Bullet::OnUpdate() {
	if (!m_OnTheGround) {
		SetDirection(m_Dir.x, m_Dir.y, m_Speed);
	}
	else if (m_OnTheGround) {
		SetMass(20);
	}
}

void Bullet::OnCollision(Entity* other) {
	if (other->IsTag(TestScene::Tag::mob1)) {
		Mob1* enemy = dynamic_cast<Mob1*>(other);
		enemy->TakeDamage(1);
	}
	if (other->IsTag(TestScene::Tag::player)) {
		Player* player = dynamic_cast<Player*>(other);
		if (IsBulletOnGround()) player->AddBullet(1);
		else if (other != m_Caster && !IsBulletOnGround()) player->TakeDamage(1);
	}
	if(other != m_Caster)Destroy();
}

bool Bullet::IsBulletOnGround() {
	return m_OnTheGround;
}