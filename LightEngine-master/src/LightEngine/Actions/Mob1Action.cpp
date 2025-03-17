#include "../Actions/Mob1Action.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"

#define DETECTING_RANGE 300.f
#define ATTACK_RANGE  50.f

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob1Action_Walking::OnStart(Mob1* owner)
{
}

void Mob1Action_Walking::OnUpdate(Mob1* owner)
{
	owner->m_WalkingTimer -= owner->GetDeltaTime();
	owner->SetDirection(m_Dir.x, m_Dir.y,200);
	if (owner->m_WalkingTimer <= 0) {
		owner->SetDirection(m_Dir.x = -m_Dir.x, m_Dir.y = -m_Dir.y, 200);
		owner->m_WalkingTimer = 3.f;
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
	owner->m_ShootCooldown -= owner->GetDeltaTime();
	if (owner->m_ShootCooldown <= 0) {
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