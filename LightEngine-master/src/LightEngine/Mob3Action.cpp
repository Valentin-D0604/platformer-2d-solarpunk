#include "Mob3Action.h"
#include "TestScene.h"
#include "Player.h"
#include "Bullet.h"

#include "Utils/Utils.h"

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob3Action_Walking::OnStart(Mob3* owner)
{
}

void Mob3Action_Walking::OnUpdate(Mob3* owner)
{
	owner->m_walkingTimer -= owner->GetDeltaTime();
	owner->SetDirection(dir.x, dir.y, 200);
	if (owner->m_walkingTimer <= 0) {
		owner->SetDirection(dir.x = -dir.x, dir.y = -dir.y, 200);
		owner->m_walkingTimer = 3.f;
	}
}

void Mob3Action_Walking::OnEnd(Mob3* owner)
{
}

//----------------------------------------Chasing-------------------------
void Mob3Action_Chasing::OnStart(Mob3* owner)
{
}

void Mob3Action_Chasing::OnUpdate(Mob3* owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
	Player* player = scene->GetPlayer();
	owner->GoToDirection(player->GetPosition().x, player->GetPosition().y, 200);
	//	std::cout << "chasing";
}

void Mob3Action_Chasing::OnEnd(Mob3* owner)
{
}

//-----------------------------------------Attacking-------------------------
void Mob3Action_Attacking::OnStart(Mob3* owner)
{
}

void Mob3Action_Attacking::OnUpdate(Mob3* owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
	Player* player = scene->GetPlayer();
	owner->m_shootCooldown -= owner->GetDeltaTime();
	//if ((owner->GetPosition().x <= player->GetPosition().x + 50 && owner->GetPosition().x >= player->GetPosition().x - 50 && owner->GetPosition().y <= player->GetPosition().y + 50 && owner->GetPosition().y >= player->GetPosition().y - 50)) {
	if (owner->m_shootCooldown <= 0) {
		owner->Attack();
	}
	//	}
}

void Mob3Action_Attacking::OnEnd(Mob3* owner)
{
}

//-----------------------------------------Idle-------------------------
void Mob3Action_Idle::OnStart(Mob3* owner)
{
}

void Mob3Action_Idle::OnUpdate(Mob3* owner)
{
}

void Mob3Action_Idle::OnEnd(Mob3* owner)
{
}
//------------------------------------------------------------------------