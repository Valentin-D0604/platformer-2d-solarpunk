#include "../Entity/Explode.h"
#include "../Collision/RectangleCollider.h"

#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Entity/Mob1.h"
#include "../Entity/Mob2.h"
#include "../Entity/Mob3.h"
#include "../Entity/Bullet.h"
#include "../Graphics/Sprite.h"

#include "../Graphics/Debug.h"
#include "../Managers/Managers.h"
#include <iostream>


void Explode::OnInitialize()
{
	m_Sprite = new Sprite();
	m_Sprite->setTexture(*(GET_MANAGER(ResourceManager)->getTexture("test")));

	SetTag(TestScene::Tag::mob1);
	sf::Vector2f pos = { GetPosition().x,GetPosition().y };
	m_Collider = new RectangleCollider(pos,{50,50});

}

void Explode::OnCollision(Entity* other)
{
	if (m_DamageCooldown <= 0) {
		if (other->IsTag(TestScene::Tag::player)) {
			Player* player = dynamic_cast<Player*>(other);
			if(!player->IsParry()) player->TakeDamage(2);
		}
		if (other->IsTag(TestScene::Tag::mob1)) {
			Mob1* mob1 = dynamic_cast<Mob1*>(other);
			mob1->TakeDamage(2);
		}
		if (other->IsTag(TestScene::Tag::mob2)) {
			Mob2* mob2 = dynamic_cast<Mob2*>(other);
			mob2->TakeDamage(2);
		}

		if (other->IsTag(TestScene::Tag::bullet)) {
			other->Destroy();
		}
		m_DamageCooldown = 1.f;
	}
}

void Explode::OnUpdate()
{
	m_duration -= GetDeltaTime();
	if (m_duration <= 0) {
		Destroy();
	}
}
