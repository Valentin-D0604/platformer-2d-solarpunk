#include "../Entity/Collectable.h"
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

void Collectable::InitCollec(sf::Vector2f position, sf::Vector2f direction, Entity* caster) {
	m_caster = caster;
	Utils::Normalize(direction);
	m_pos = position;
	m_dir = direction;
	SetPosition(position.x, position.y);
}

void Collectable::OnInitialize() {
	m_sprite = new Sprite();
	m_sprite->setTexture(*(GET_MANAGER(ResourceManager)->GetTexture("test")));

	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	sf::Vector2f size = { 50,50 };
	m_collider = new RectangleCollider(pos, size);
	SetTag(TestScene::Tag::PowerUp);
}

void Collectable::OnUpdate() {
	m_lifeTime -= GetDeltaTime();
	SetMass(75);
}

void Collectable::OnCollision(Entity* other) {
	Player* player = dynamic_cast<Player*>(other);
	if (other->IsTag(TestScene::Tag::player)) {
		if (other != m_caster && !player->IsParry()) player->TakeDamage(1); // playe take damage
	}
	if (other != m_caster && other->IsTag(TestScene::Tag::player)) {
		player->AddBuff(1);
		Destroy();
	}
	if (m_lifeTime <= 0) Destroy();
}
