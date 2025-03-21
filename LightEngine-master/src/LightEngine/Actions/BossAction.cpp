#include "BossAction.h"
#include "../Scene/TestScene.h"
#include "../Entity/Player.h"
#include "../Managers/Managers.h"


// ----------------------------------------- IDLE -------------------------
void BossAction_Idle::OnStart(Boss* _owner)
{
	m_idleTimer = 5.0f;
	_owner->m_isIdle = true;
	_owner->SetAnimation("idle");
}

void BossAction_Idle::OnUpdate(Boss* _owner)
{
	m_idleTimer -= GET_MANAGER(GameManager)->GetDeltaTime();
	if (_owner->GetPosition() != _owner->m_position)
	{
		_owner->GoToPosition(_owner->m_position.x, _owner->m_position.y, 0.1f);
	}
	if (m_idleTimer <= 0.0f)
	{
		if (AttackType == 0)
		{
			_owner->CheckState(BossActionType::groundSmash);
			AttackType = 1;
		}
		else
		{
			_owner->CheckState(BossActionType::grabRock);
			AttackType = 0;
		}
	}
}

void BossAction_Idle::OnEnd(Boss* _owner)
{
}

// ----------------------------------------- GroundSmash -------------------------
void BossAction_GroundSmash::OnStart(Boss* _owner)
{
	if (_owner->GetDistanceToPlayer() > 800) return;
	m_Timer = 4.0f;
	_owner->m_isGroundSmashing = true;
	_owner->SetAnimation("slam");
}

void BossAction_GroundSmash::OnUpdate(Boss* _owner) 
{
	m_Timer -= GET_MANAGER(GameManager)->GetDeltaTime();

}

void BossAction_GroundSmash::OnEnd(Boss* _owner) 
{

}

// ----------------------------------------- GRAB ROCK -------------------------
void BossAction_GrabRock::OnStart(Boss* _player)
{
	if (_player->GetDistanceToPlayer() > 800) return;
	m_Timer = 4.0f;
	_player->m_GrabRock = true;
	_player->SetAnimation("grab");
}

void BossAction_GrabRock::OnUpdate(Boss* _player)
{
	m_Timer -= GET_MANAGER(GameManager)->GetDeltaTime();
	if (m_Timer <= 0.0f)
	{
		_player->CheckState(BossActionType::throwRock);
		_player->m_GrabRock = false;

	}
}

void BossAction_GrabRock::OnEnd(Boss* _player)
{

}

// ----------------------------------------- LANCEMENT DE PROJECTILES -------------------------
void BossAction_Throwing::OnStart(Boss* _owner) 
{
	if (_owner->GetDistanceToPlayer() > 800) return;
	m_Timer = 4.0f;
	_owner->m_isThrowing = true;
	_owner->SetAnimation("throw");
}

void BossAction_Throwing::OnUpdate(Boss* _owner) 
{
	m_Timer -= GET_MANAGER(GameManager)->GetDeltaTime();
	if (m_Timer <= 0.0f)
	{
		_owner->CheckState(BossActionType::retreat);
	}
}

void BossAction_Throwing::OnEnd(Boss* _owner) 
{

}
//------------------------------------------RETRAIT --------------------------------
void BossAction_Retreat::OnStart(Boss* _owner)
{
	if (_owner->GetDistanceToPlayer() > 800) return;
	m_Timer = 4.0f;
	_owner->m_isRetreating = true;
	_owner->SetAnimation("retreat");
}
void BossAction_Retreat::OnUpdate(Boss* _owner) 
{
	m_Timer -= GET_MANAGER(GameManager)->GetDeltaTime();
	if (m_Timer <= 2.0f)
	{
		if (!createprojectil)
		{
			Bullet* bullet = _owner->CreateEntity<Bullet>();
			bullet->SetDirection(0, 1, 9.f);
			bullet->InitBullet(_owner->GetPosition(), {0, 1},_owner);
			bullet->SetMass(1);
			bullet->SetGravityDirection(sf::Vector2f(0, 1));
			//over the players head
			Player* player = dynamic_cast<TestScene*>(_owner->GetScene())->GetPlayer();
			sf::Vector2f playerPos = player->GetPosition();
			bullet->SetPosition(playerPos.x,playerPos.y-500);
			createprojectil = true;
		}

	}

	if (m_Timer <= 0.0f)
	{
		_owner->CheckState(BossActionType::idle);
		createprojectil = false;
	}

}
void BossAction_Retreat::OnEnd(Boss* _owner)
{

}