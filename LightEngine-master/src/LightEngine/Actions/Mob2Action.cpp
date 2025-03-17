#include "Mob2Action.h"
#include "TestScene.h"
#include "Player.h"
#include "Bullet.h"

#include "Utils/Utils.h"

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
	owner->m_shootCooldown -= owner->GetDeltaTime();
	if (owner->m_shootCooldown <= 0) {
		owner->Attack();
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