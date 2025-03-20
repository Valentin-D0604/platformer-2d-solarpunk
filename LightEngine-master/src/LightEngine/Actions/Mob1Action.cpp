#include "../Actions/Mob1Action.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Graphics/SpriteSheet.h"

#define DETECTING_RANGE 300.f
#define ATTACK_RANGE  50.f

#include <iostream>
//-----------------------------------------walking-------------------------
void Mob1Action_Walking::OnStart(Mob1* _owner)
{
	dynamic_cast<SpriteSheet*>(_owner->m_sprite)->SetAnimation("walk");
}

void Mob1Action_Walking::OnUpdate(Mob1* _owner)
{
	_owner->m_walkingTimer -= _owner->GetDeltaTime();
	_owner->SetDirection(m_Dir.x, m_Dir.y,200);
	if (_owner->m_walkingTimer <= 0) {
		_owner->SetDirection(m_Dir.x = -m_Dir.x, m_Dir.y = -m_Dir.y, 200);
		_owner->m_walkingTimer = 3.f;
	}
}

void Mob1Action_Walking::OnEnd(Mob1* _owner)
{
}

//----------------------------------------Chasing-------------------------
void Mob1Action_Chasing::OnStart(Mob1* _owner)
{
	dynamic_cast<SpriteSheet*>(_owner->m_sprite)->SetAnimation("walk");
}

void Mob1Action_Chasing::OnUpdate(Mob1* _owner)
{
	TestScene* scene = dynamic_cast<TestScene*>(_owner->GetScene());
	Player* player = scene->GetPlayer();
	_owner->GoToDirection(player->GetPosition().x, _owner->GetPosition().y, 200);
//	std::cout << "chasing";
}

void Mob1Action_Chasing::OnEnd(Mob1* _owner)
{
}

//-----------------------------------------Attacking-------------------------
void Mob1Action_Attacking::OnStart(Mob1* _owner)
{
		dynamic_cast<SpriteSheet*>(_owner->m_sprite)->SetAnimation("attack");
}

void Mob1Action_Attacking::OnUpdate(Mob1* _owner)
{
	_owner->m_shootCooldown -= _owner->GetDeltaTime();
	if (_owner->m_shootCooldown <= 0) {
		dynamic_cast<SpriteSheet*>(_owner->m_sprite)->SetAnimation("attack");
		_owner->Attack();
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