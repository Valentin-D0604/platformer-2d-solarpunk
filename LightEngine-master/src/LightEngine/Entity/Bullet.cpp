#include "../Entity/Bullet.h"
#include "../Collision/RectangleCollider.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Entity/Mob1.h"
#include "../Entity/Mob2.h"
#include "../Entity/Mob3.h"

#include "../Graphics/Sprite.h"
#include "../Managers/Managers.h"
#include"../Utils/Utils.h"


#include <iostream>

void Bullet::InitBullet(sf::Vector2f _position, sf::Vector2f _direction,Entity* _caster) {
	m_caster = _caster;
	Utils::Normalize(_direction);
	m_pos = _position;
	m_dir = _direction;
	SetPosition(_position.x, _position.y);
}

void Bullet::OnInitialize() {
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("Bullet")));
	m_sprite->setScale(0.1, 0.1);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);
	m_collider->SetGizmo(true);
	m_sprite->setPosition(m_collider->GetPosition().x, m_collider->GetPosition().y);
	SetTag(TestScene::Tag::bullet);
}

void Bullet::OnUpdate() {
	m_changeDirection -= GetDeltaTime();
	m_lifeTime -= GetDeltaTime();
	SetDirection(m_dir.x, m_dir.y, 200);
	m_spawnTime -= GetDeltaTime();
}

void Bullet::OnDestroy()
{

}

void Bullet::OnCollision(Entity* other) {
	if (m_spawnTime > 0) { return; }
	Player* player = dynamic_cast<Player*>(other);
	if (other->IsTag(TestScene::Tag::mob1) && !m_caster->IsTag(TestScene::Tag::mob1)) {
		Mob1* enemy = dynamic_cast<Mob1*>(other);
		if (enemy != m_caster) enemy->TakeDamage(1);
	}
	if (other->IsTag(TestScene::Tag::mob2) && !m_caster->IsTag(TestScene::Tag::mob2)) {
		Mob2* enemy = dynamic_cast<Mob2*>(other);
		if (enemy != m_caster) enemy->TakeDamage(1);
	}
	if (other->IsTag(TestScene::Tag::mob3) && !m_caster->IsTag(TestScene::Tag::mob3)) {
		Mob3* enemy = dynamic_cast<Mob3*>(other);
		if (enemy != m_caster) enemy->TakeDamage(1);
	}
	if (other->IsTag(TestScene::Tag::player)) {
		if (other != m_caster && !player->IsParry()) player->TakeDamage(1); // playe take damage
		else if (other != m_caster && player->IsParry() && m_changeDirection <= 0) {
			m_dir = -m_dir;
			m_changeDirection = 2.f;
			m_caster = player;
		}
	}
	if (other != m_caster && !other->IsTag(TestScene::Tag::player)&& !other->IsTag(TestScene::Tag::platform) && !other->IsTag(TestScene::Tag::PowerUp)) {
		if (other->IsTag(TestScene::Tag::player) && m_caster->IsTag(TestScene::Tag::player)) return;
		if (other->IsTag(TestScene::Tag::mob1) && m_caster->IsTag(TestScene::Tag::mob1)) return;
		if (other->IsTag(TestScene::Tag::mob2) && m_caster->IsTag(TestScene::Tag::mob2)) return;
		if (other->IsTag(TestScene::Tag::mob3) && m_caster->IsTag(TestScene::Tag::platform)) return;
		Destroy();
	}
	if (other != m_caster && other->IsTag(TestScene::Tag::player)) {
		if (other != m_caster && !player->IsParry()) Destroy();
	}
	if (m_lifeTime <= 0) {
		Destroy();
	}
}
