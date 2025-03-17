#include "../Entity/Bullet.h"
#include "../Collision/RectangleCollider.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Entity/Mob1.h"
#include "../Entity/Mob2.h"

#include "../Graphics/Sprite.h"
#include "../Managers/Managers.h"
#include"../Utils/Utils.h"


#include <iostream>

void Bullet::InitBullet(sf::Vector2f position, sf::Vector2f direction,Entity* caster, bool state) {
	m_caster = caster;
	Utils::Normalize(direction);
	m_pos = position;
	m_dir = direction;
	m_onTheGround = state;
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
	m_changeDirection -= GetDeltaTime();
	m_lifeTime -= GetDeltaTime();
	if (!m_onTheGround) {
		SetDirection(m_dir.x, m_dir.y, 200);
	}
	else if (m_onTheGround) {
		SetMass(20);
	}
}
void Bullet::OnCollision(Entity* other) {
	Player* player = dynamic_cast<Player*>(other);
	if (other->IsTag(TestScene::Tag::mob1)) {
		Mob1* enemy = dynamic_cast<Mob1*>(other);
		enemy->TakeDamage(1);
	}
	if (other->IsTag(TestScene::Tag::mob2)) {
		Mob2* enemy = dynamic_cast<Mob2*>(other);
		if (enemy != m_caster && !IsBulletOnGround()) enemy->TakeDamage(1);
	}
	if (other->IsTag(TestScene::Tag::player)) {
	if (IsBulletOnGround()) player->AddBuff(1); // drop
		else if (other != m_caster && !IsBulletOnGround() && !player->IsParry()) player->TakeDamage(1); // playe take damage
		else if (other != m_caster && !IsBulletOnGround() && player->IsParry() && m_changeDirection <= 0) { m_dir = -m_dir; m_changeDirection = 1.f; m_caster = player; } // player parry bullet
	}
	if (other != m_caster && !other->IsTag(TestScene::Tag::player)) {
		Destroy();
	}
	if (other != m_caster && other->IsTag(TestScene::Tag::player)) {
		if (other != m_caster && !player->IsParry()) Destroy();
	}
	if (m_lifeTime <= 0) Destroy();
}

bool Bullet::IsBulletOnGround() {
	return m_onTheGround;
}