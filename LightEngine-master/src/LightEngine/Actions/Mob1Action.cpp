#include "Mob1Action.h"
#include "TestScene.h"
#include "Player.h"

#define DETECTING_RANGE 300.f
#define ATTACK_RANGE  50.f

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob1Action_Walking::OnStart(Mob1* owner)
{
}

void Mob1Action_Walking::OnUpdate(Mob1* owner)
{
	owner->m_walkingTimer -= owner->GetDeltaTime();
	owner->SetDirection(dir.x, dir.y, 200);
	if (owner->m_walkingTimer <= 0) {
		owner->SetDirection(dir.x = -dir.x, dir.y = -dir.y, 200);
		owner->m_walkingTimer = 3.f;
	}
}

void Mob1Action_Walking::OnEnd(Mob1* owner)
{
}

//----------------------------------------Chasing-------------------------
void Mob1Action_Chasing::OnStart(Mob1* owner)
{
}

void Mob1Action_Chasing::OnUpdate(Mob1* owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(owner->GetScene());
	Player* player = scene->GetPlayer();
	owner->GoToDirection(player->GetPosition().x, player->GetPosition().y, 200);
//	std::cout << "chasing";
}

void Mob1Action_Chasing::OnEnd(Mob1* owner)
{
}

//-----------------------------------------Attacking-------------------------
void Mob1Action_Attacking::OnStart(Mob1* owner)
{
}

void Mob1Action_Attacking::OnUpdate(Mob1* owner)
{
	owner->m_shootCooldown -= owner->GetDeltaTime();
	if (owner->m_shootCooldown <= 0) {
		owner->Attack();
	}
//	}
}

void Mob1Action_Attacking::OnEnd(Mob1* owner)
{
}

//-----------------------------------------Idle-------------------------
void Mob1Action_Idle::OnStart(Mob1* owner)
{
}

void Mob1Action_Idle::OnUpdate(Mob1* owner)
{
}

void Mob1Action_Idle::OnEnd(Mob1* owner)
{
}
//------------------------------------------------------------------------