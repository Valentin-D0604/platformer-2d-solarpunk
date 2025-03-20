#include "../Actions/Mob2Action.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Entity/Bullet.h"

#include "../Utils/Utils.h"

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob2Action_Walking::OnStart(Mob2* _owner)
{
}

void Mob2Action_Walking::OnUpdate(Mob2* _owner)
{
	_owner->m_walkingTimer -= _owner->GetDeltaTime();
	_owner->SetDirection(m_dir.x, m_dir.y, 200);
	if (_owner->m_walkingTimer <= 0) {
		_owner->SetDirection(m_dir.x = -m_dir.x, m_dir.y = -m_dir.y, 200);
		_owner->m_walkingTimer = 3.f;
	}
}

void Mob2Action_Walking::OnEnd(Mob2* _owner)
{
}

//----------------------------------------Chasing-------------------------
void Mob2Action_Chasing::OnStart(Mob2* _owner)
{
}

void Mob2Action_Chasing::OnUpdate(Mob2* _owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();
	_owner->GoToDirection(player->GetPosition().x, _owner->GetPosition().y, 200);
	//	std::cout << "chasing";
}

void Mob2Action_Chasing::OnEnd(Mob2* _owner)
{
}

//-----------------------------------------Attacking-------------------------
void Mob2Action_Attacking::OnStart(Mob2* _owner)
{
}

void Mob2Action_Attacking::OnUpdate(Mob2* _owner)
{
	_owner->m_shootCooldown -= _owner->GetDeltaTime();
	if (_owner->m_shootCooldown <= 0) {
		_owner->Attack();
	}
	//	}
}

void Mob2Action_Attacking::OnEnd(Mob2* _owner)
{
}

//-----------------------------------------Idle-------------------------
void Mob2Action_Idle::OnStart(Mob2* _owner)
{
}

void Mob2Action_Idle::OnUpdate(Mob2* _owner)
{
}

void Mob2Action_Idle::OnEnd(Mob2* _owner)
{
}
//------------------------------------------------------------------------