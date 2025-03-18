#include "../Actions/Mob3Action.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Entity/Bullet.h"

#include "../Utils/Utils.h"

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob3Action_Walking::OnStart(Mob3* _owner)
{
}

void Mob3Action_Walking::OnUpdate(Mob3* _owner)
{
	_owner->m_walkingTimer -= _owner->GetDeltaTime();
	_owner->SetDirection(m_dir.x, m_dir.y, _owner->m_Speed);
	if (_owner->m_walkingTimer <= 0) {
		_owner->SetDirection(m_dir.x = -m_dir.x, m_dir.y = -m_dir.y, _owner->m_Speed);
		_owner->m_walkingTimer = 3.f;
	}
}

void Mob3Action_Walking::OnEnd(Mob3* _owner)
{
}

//----------------------------------------Chasing-------------------------
void Mob3Action_Chasing::OnStart(Mob3* _owner)
{
}

void Mob3Action_Chasing::OnUpdate(Mob3* _owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();
	_owner->GoToDirection(player->GetPosition().x, player->GetPosition().y, _owner->m_Speed);
	//	std::cout << "chasing";
}

void Mob3Action_Chasing::OnEnd(Mob3* _owner)
{
}

//-----------------------------------------Attacking-------------------------
void Mob3Action_Attacking::OnStart(Mob3* _owner)
{
}

void Mob3Action_Attacking::OnUpdate(Mob3* _owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();
	_owner->m_shootCooldown -= _owner->GetDeltaTime();
	if (_owner->m_shootCooldown <= 0) {
		_owner->Attack();
	}
	//	}
}

void Mob3Action_Attacking::OnEnd(Mob3* _owner)
{
}

//-----------------------------------------Idle-------------------------
void Mob3Action_Idle::OnStart(Mob3* _owner)
{
}

void Mob3Action_Idle::OnUpdate(Mob3* _owner)
{
}

void Mob3Action_Idle::OnEnd(Mob3* _owner)
{
}
//------------------------------------------------------------------------