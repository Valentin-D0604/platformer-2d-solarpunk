#include "Mob1Action.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob1Action_Walking::OnStart(Mob1* _owner)
{
}

void Mob1Action_Walking::OnUpdate(Mob1* _owner)
{
	_owner->m_WalkingTimer -= _owner->GetDeltaTime();
	_owner->SetDirection(m_Dir.x, m_Dir.y, 200);
	if (_owner->m_WalkingTimer <= 0) {
		_owner->SetDirection(m_Dir.x = -m_Dir.x, m_Dir.y = -m_Dir.y, 200);
		_owner->m_WalkingTimer = 3.f;
		std::cout << "walking";
	}
}

void Mob1Action_Walking::OnEnd(Mob1* _owner)
{
}

//----------------------------------------Chasing-------------------------
void Mob1Action_Chasing::OnStart(Mob1* _owner)
{
}

void Mob1Action_Chasing::OnUpdate(Mob1* _owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();
	_owner->GoToDirection(player->GetPosition().x, player->GetPosition().y, 200);
//	std::cout << "chasing";
}

void Mob1Action_Chasing::OnEnd(Mob1* _owner)
{
}

//-----------------------------------------Attacking-------------------------
void Mob1Action_Attacking::OnStart(Mob1* _owner)
{
}

void Mob1Action_Attacking::OnUpdate(Mob1* _owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();
	_owner->m_ShootCooldown -= _owner->GetDeltaTime();
	//if ((owner->GetPosition().x <= player->GetPosition().x + 50 && owner->GetPosition().x >= player->GetPosition().x - 50 && owner->GetPosition().y <= player->GetPosition().y + 50 && owner->GetPosition().y >= player->GetPosition().y - 50)) {
	if (_owner->m_ShootCooldown <= 0) {
		player->TakeDamage(1);
		_owner->m_ShootCooldown = 2.f;
		//std::cout << "attack";
	}
//	}
}

void Mob1Action_Attacking::OnEnd(Mob1* _owner)
{
}

//-----------------------------------------Idle-------------------------
void Mob1Action_Idle::OnStart(Mob1* _owner)
{
}

void Mob1Action_Idle::OnUpdate(Mob1* _owner)
{
}

void Mob1Action_Idle::OnEnd(Mob1* _owner)
{
}
//------------------------------------------------------------------------