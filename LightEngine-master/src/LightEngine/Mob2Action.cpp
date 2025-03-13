#include "Mob2Action.h"
#include "TestScene.h"
#include "Player.h"
#include "Bullet.h"

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob2Action_Walking::OnStart(Mob2* owner)
{
}

void Mob2Action_Walking::OnUpdate(Mob2* owner)
{
	owner->m_walkingTimer -= owner->GetDeltaTime();
	owner->SetDirection(dir.x, dir.y, 200);
	if (owner->m_walkingTimer <= 0) {
		owner->SetDirection(dir.x = -dir.x, dir.y = -dir.y, 200);
		owner->m_walkingTimer = 3.f;
	}
}

void Mob2Action_Walking::OnEnd(Mob2* owner)
{
}

//----------------------------------------Chasing-------------------------
void Mob2Action_Chasing::OnStart(Mob2* owner)
{
}

void Mob2Action_Chasing::OnUpdate(Mob2* owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
	Player* player = scene->GetPlayer();
	owner->GoToDirection(player->GetPosition().x, player->GetPosition().y, 200);
	//	std::cout << "chasing";
}

void Mob2Action_Chasing::OnEnd(Mob2* owner)
{
}

//-----------------------------------------Attacking-------------------------
void Mob2Action_Attacking::OnStart(Mob2* owner)
{
}

void Mob2Action_Attacking::OnUpdate(Mob2* owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
	Player* player = scene->GetPlayer();
	owner->m_shootCooldown -= owner->GetDeltaTime();
	//if ((owner->GetPosition().x <= player->GetPosition().x + 50 && owner->GetPosition().x >= player->GetPosition().x - 50 && owner->GetPosition().y <= player->GetPosition().y + 50 && owner->GetPosition().y >= player->GetPosition().y - 50)) {
	if (owner->m_shootCooldown <= 0) {
		owner->m_shootCooldown = 2.f;
		Bullet* bullet = owner->CreateEntity<Bullet>();
		std::cout << owner;
		bullet->InitBullet(owner->GetPosition(), player->GetPosition(), owner, false);
		bullet->setMass(1);
		bullet->setGravityDirection(sf::Vector2f(0, 1));
		std::cout << "attack";
	}
	//	}
}

void Mob2Action_Attacking::OnEnd(Mob2* owner)
{
}

//-----------------------------------------Idle-------------------------
void Mob2Action_Idle::OnStart(Mob2* owner)
{
}

void Mob2Action_Idle::OnUpdate(Mob2* owner)
{
}

void Mob2Action_Idle::OnEnd(Mob2* owner)
{
}
//------------------------------------------------------------------------