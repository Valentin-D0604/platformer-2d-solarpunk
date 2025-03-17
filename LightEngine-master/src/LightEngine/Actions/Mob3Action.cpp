#include "../Actions/Mob3Action.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Entity/Bullet.h"

#include "../Utils/Utils.h"

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob3Action_Walking::OnStart(Mob3* owner)
{
}

void Mob3Action_Walking::OnUpdate(Mob3* owner)
{
	owner->m_walkingTimer -= owner->GetDeltaTime();
	owner->SetDirection(dir.x, dir.y, owner->m_Speed);
	if (owner->m_walkingTimer <= 0) {
		owner->SetDirection(dir.x = -dir.x, dir.y = -dir.y, owner->m_Speed);
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
	owner->GoToDirection(player->GetPosition().x, player->GetPosition().y, owner->m_Speed);
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